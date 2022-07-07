#ifndef ORMXX_ORMXX_H
#define ORMXX_ORMXX_H

#include <cstddef>
#include <list>
#include <memory>
#include <mutex>
#include <type_traits>
#include <unordered_map>

#include "./interface/execute_result.h"       // IWYU pragma: export
#include "./interface/index.h"                // IWYU pragma: export
#include "./internal/inject_utility.h"        // IWYU pragma: export
#include "./internal/macros.h"                // IWYU pragma: export
#include "./options/index.h"                  // IWYU pragma: export
#include "./sql/generate_create_table_sql.h"  // IWYU pragma: export
#include "./sql/generate_delete_sql.h"        // IWYU pragma: export
#include "./sql/generate_drop_table_sql.h"    // IWYU pragma: export
#include "./sql/generate_insert_sql.h"        // IWYU pragma: export
#include "./sql/generate_update_sql.h"        // IWYU pragma: export

namespace ormxx {

class ORMXX {
public:
    using ConnectionType = Adaptor::ConnectionType;

public:
    struct Options {
        size_t max_idle_connection{128};
    };

    class Builder {
    public:
        Builder() = delete;
        Builder(Adaptor* adaptor) : adaptor_(adaptor) {}

        Builder& WithMaxIdleConnection(size_t max_idle_connection) {
            options_.max_idle_connection = max_idle_connection;
            return *this;
        }

        ORMXX Build() {
            return ORMXX(adaptor_, options_);
        }

        ORMXX* BuildPtr() {
            return new ORMXX(adaptor_, options_);
        }

    private:
        Adaptor* adaptor_;
        Options options_;
    };

private:
    struct connectionPoolNode {
        std::mutex mutex_;
        std::list<Connection*> pool;
    };

public:
    ORMXX() = delete;

    ORMXX(Adaptor* adaptor, const Options& options) : adaptor_(adaptor), options_(options) {}

    ~ORMXX() {
        if (adaptor_) {
            delete adaptor_;
        }

        for (auto& [k, v] : connection_pool_node_map_) {
            while (!v.pool.empty()) {
                auto& connection = v.pool.front();
                v.pool.pop_front();

                connection->Close();
                delete connection;
            }
        }
    }

    ResultOr<std::unique_ptr<ExecuteResult>> Execute(const std::string& sql) {
        auto conn_res = getWriteConnection();
        if (!conn_res.IsOK()) {
            return conn_res;
        }

        auto* conn = conn_res.Value();
        auto res = conn->Execute(sql);
        releaseWriteConnection(conn);

        return res;
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const std::string& sql) {
        auto conn_res = getReadConnection();
        if (!conn_res.IsOK()) {
            return conn_res;
        }

        auto* conn = conn_res.Value();
        auto res = conn->ExecuteQuery(sql);
        releaseReadConnection(conn);

        return res;
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const std::string& sql) {
        auto conn_res = getWriteConnection();
        if (!conn_res.IsOK()) {
            return conn_res;
        }

        auto* conn = conn_res.Value();
        auto res = conn->ExecuteUpdate(sql);
        releaseWriteConnection(conn);

        return res;
    }

    template <typename T>
    Result CheckSchema() {
        auto sql_res = GenerateCreateTableSQL<T>();
        if (!sql_res.IsOK()) {
            return sql_res;
        }

        return Result::Builder(Result::ErrorCode::OK).Build();
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> DropTable() {
        auto sql_res = GenerateDropTableSQL<T>();
        if (!sql_res.IsOK()) {
            return sql_res;
        }

        return Execute(sql_res.Value());
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> CreateTable() {
        auto sql_res = GenerateCreateTableSQL<T>();
        if (!sql_res.IsOK()) {
            return sql_res;
        }

        return Execute(sql_res.Value());
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(T* t) {
        auto sql_res = GenerateInsertSQL(t);
        if (!sql_res.IsOK()) {
            return sql_res;
        }

        auto execute_res = ExecuteUpdate(sql_res.Value());

        if constexpr (!std::is_const_v<T>) {
            if (execute_res.IsOK()) {
                internal::InjectUtility::ClearIsSetMap(t);
            }
        }

        return execute_res;
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(std::vector<T>* t) {
        auto sql_res = GenerateInsertSQL(t);
        if (!sql_res.IsOK()) {
            return sql_res;
        }

        auto execute_res = ExecuteUpdate(sql_res.Value());

        if (execute_res.IsOK()) {
            for (auto& _t : *t) {
                internal::InjectUtility::ClearIsSetMap(&_t);
            }
        }

        return execute_res;
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(const std::vector<T>* t) {
        auto sql_res = GenerateInsertSQL(t);
        if (!sql_res.IsOK()) {
            return sql_res;
        }

        return ExecuteUpdate(sql_res.Value());
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(T t) {
        return Insert(&t);
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Delete(T* t) {
        auto sql_res = GenerateDeleteSQL(t);
        if (!sql_res.IsOK()) {
            return sql_res;
        }

        return ExecuteUpdate(sql_res.Value());
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Delete(T t) {
        return Delete(&t);
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Update(T* t) {
        auto sql_res = GenerateUpdateSQL(t);
        if (!sql_res.IsOK()) {
            return sql_res;
        }

        auto execute_res = ExecuteUpdate(sql_res.Value());

        if constexpr (!std::is_const_v<T>) {
            if (execute_res.IsOK()) {
                internal::InjectUtility::ClearIsSetMap(t);
            }
        }

        return execute_res;
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Update(T t) {
        return Update(&t);
    }

private:
    ResultOr<Connection*> getConnection(ConnectionType connection_type = ConnectionType::WRITE) {
        auto& node = connection_pool_node_map_[connection_type];
        std::unique_lock<std::mutex> lock(node.mutex_);

        if (!node.pool.empty()) {
            auto* connection = node.pool.front();
            node.pool.pop_front();
            connection->ReConnect();
            return connection;
        }

        return adaptor_->GetConnection(connection_type);
    }

    ResultOr<Connection*> getWriteConnection() {
        return getConnection(ConnectionType::WRITE);
    }

    ResultOr<Connection*> getReadConnection() {
        return getConnection(ConnectionType::READ);
    }

    void releaseConnection(Connection* connection, ConnectionType connection_type = ConnectionType::WRITE) {
        auto& node = connection_pool_node_map_[connection_type];
        std::unique_lock<std::mutex> lock(node.mutex_);

        if (node.pool.size() < options_.max_idle_connection) {
            node.pool.push_back(connection);
        } else {
            connection->Close();
            delete connection;
        }
    }

    void releaseWriteConnection(Connection* connection) {
        releaseConnection(connection, ConnectionType::WRITE);
    }

    void releaseReadConnection(Connection* connection) {
        releaseConnection(connection, ConnectionType::READ);
    }

private:
    std::unordered_map<ConnectionType, connectionPoolNode> connection_pool_node_map_;

    Adaptor* adaptor_;

    Options options_;
};

}  // namespace ormxx

#endif  // ORMXX_ORMXX_H
