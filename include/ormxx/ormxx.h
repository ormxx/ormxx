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
#include "result/macros.h"

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
        RESULT_VALUE_OR_RETURN(*conn, getWriteConnection());

        auto res = conn->Execute(sql);
        releaseWriteConnection(conn);

        return res;
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const std::string& sql) {
        RESULT_VALUE_OR_RETURN(*conn, getReadConnection());

        auto res = conn->ExecuteQuery(sql);
        releaseReadConnection(conn);

        return res;
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const std::string& sql) {
        RESULT_VALUE_OR_RETURN(*conn, getWriteConnection());

        auto res = conn->ExecuteUpdate(sql);
        releaseWriteConnection(conn);

        return res;
    }

    template <typename T>
    Result CheckSchema() {
        return GenerateCreateTableSQL<T>();
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> DropTable() {
        RESULT_VALUE_OR_RETURN(const sql, GenerateDropTableSQL<T>());
        return Execute(sql);
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> CreateTable() {
        RESULT_VALUE_OR_RETURN(const sql, GenerateCreateTableSQL<T>());
        return Execute(sql);
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(T* t) {
        RESULT_VALUE_OR_RETURN(const sql, GenerateInsertSQL<T>(t));
        RESULT_VALUE_OR_RETURN(execute_res, ExecuteUpdate(sql));

        if constexpr (!std::is_const_v<T>) {
            internal::InjectUtility::ClearIsSetMap(t);
        }

        return execute_res;
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(std::vector<T>* t) {
        RESULT_VALUE_OR_RETURN(const sql, GenerateInsertSQL<T>(t));
        RESULT_VALUE_OR_RETURN(execute_res, ExecuteUpdate(sql));

        for (auto& _t : *t) {
            internal::InjectUtility::ClearIsSetMap(&_t);
        }

        return execute_res;
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(const std::vector<T>* t) {
        RESULT_VALUE_OR_RETURN(const sql, GenerateInsertSQL<T>(t));
        return ExecuteUpdate(sql);
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Insert(T t) {
        return Insert(&t);
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Delete(T* t) {
        RESULT_VALUE_OR_RETURN(const sql, GenerateDeleteSQL<T>(t));
        return ExecuteUpdate(sql);
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Delete(T t) {
        return Delete(&t);
    }

    template <typename T>
    ResultOr<std::unique_ptr<ExecuteResult>> Update(T* t) {
        RESULT_VALUE_OR_RETURN(const sql, GenerateUpdateSQL<T>(t));
        RESULT_VALUE_OR_RETURN(execute_res, ExecuteUpdate(sql));

        if constexpr (!std::is_const_v<T>) {
            internal::InjectUtility::ClearIsSetMap(t);
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
