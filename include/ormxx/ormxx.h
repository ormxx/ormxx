#ifndef ORMXX_ORMXX_H
#define ORMXX_ORMXX_H

#include <cstddef>
#include <list>
#include <mutex>
#include <unordered_map>

#include "./interface/adaptor.h"
#include "./interface/connection.h"
#include "./interface/result.h"
#include "./sql/generate_drop_table_sql.h"

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
    Result DropTable() {
        auto sql = GenerateDropTableSQL<T>(nullptr);
        return Execute(sql.Value());
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
