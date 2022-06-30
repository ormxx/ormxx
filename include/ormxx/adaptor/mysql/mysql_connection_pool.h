#ifndef ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_H
#define ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_H

#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "cppconn/connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "mysql_connection.h"
#include "mysql_driver.h"

#include "./mysql_connection_config.h"
#include "./mysql_helper.h"

namespace ormxx::adaptor::mysql {

class MySQLConnectionPool {
public:
    enum class ConnectionType {
        READ,
        WRITE,
    };

    struct Options {
        size_t max_idle{128};
    };

    class Builder {
    public:
        Builder& SetMaxIdle(uint32_t max_idle) {
            options_.max_idle = max_idle;
            return *this;
        }

        MySQLConnectionPool Build() {
            return MySQLConnectionPool(options_);
        }

        MySQLConnectionPool* BuildPtr() {
            return new MySQLConnectionPool(options_);
        }

    private:
        Options options_;
    };

public:
    MySQLConnectionPool() {
        init();
    }

    MySQLConnectionPool(const Options& options) : options_(options) {
        init();
    }

    ~MySQLConnectionPool() {}

    void AddConfig(const sql::ConnectOptionsMap& config, ConnectionType connection_type = ConnectionType::WRITE) {
        config_[connection_type].emplace_back(config);
    }

    void AddConfig(const MySQLConnectionConfig& config, ConnectionType connection_type = ConnectionType::WRITE) {
        config_[connection_type].emplace_back(config.GetConnectOptionsMap());
    }

    void AddWriteConfig(const sql::ConnectOptionsMap& config) {
        return AddConfig(config, ConnectionType::WRITE);
    }

    void AddWriteConfig(const MySQLConnectionConfig& config) {
        return AddConfig(config, ConnectionType::WRITE);
    }

    void AddReadConfig(const sql::ConnectOptionsMap& config) {
        return AddConfig(config, ConnectionType::READ);
    }

    void AddReadConfig(const MySQLConnectionConfig& config) {
        return AddConfig(config, ConnectionType::READ);
    }

    bool HasConfig(ConnectionType connection_type) {
        return !config_[connection_type].empty();
    }

    bool HasWriteConfig() {
        return HasConfig(ConnectionType::WRITE);
    }

    bool HasReadConfig() {
        return HasConfig(ConnectionType::READ);
    }

    std::shared_ptr<sql::Connection> GetConnection(ConnectionType connection_type = ConnectionType::WRITE) {
        if (!HasConfig(connection_type)) {
            return nullptr;
        }

        std::unique_lock<std::mutex> lock(mutex_);
        std::shared_ptr<sql::Connection> conn;

        if (connection_list_.empty()) {
            auto config = config_[connection_type];
            auto& index = config_index_[connection_type];

            // may be throw exception
            conn.reset(driver_->connect(config[index++ % config.size()]));
        } else {
            conn = connection_list_.back();
            connection_list_.pop_back();
        }

        conn->reconnect();
        return conn;
    }

    std::shared_ptr<sql::Connection> GetWriteConnection() {
        return GetConnection(ConnectionType::WRITE);
    }

    std::shared_ptr<sql::Connection> GetReadConnection() {
        return GetConnection(ConnectionType::READ);
    }

    MySQLHelper GetConnectionHelper(ConnectionType connection_type = ConnectionType::WRITE) {
        auto connection = GetConnection(connection_type);
        return MySQLHelper(connection, [connection, this]() {
            ReleaseConnection(connection);
        });
    }

    MySQLHelper GetWriteConnectionHelper() {
        return GetConnectionHelper(ConnectionType::WRITE);
    }

    MySQLHelper GetReadConnectionHelper() {
        return GetConnectionHelper(ConnectionType::READ);
    }

    void ReleaseConnection(std::shared_ptr<sql::Connection> conn) {
        std::unique_lock<std::mutex> lock(mutex_);

        if (connection_list_.size() < options_.max_idle) {
            connection_list_.emplace_back(conn);
        }
    }

protected:
    void init() {
        config_[ConnectionType::WRITE] = {};
        config_[ConnectionType::READ] = {};
        config_index_[ConnectionType::WRITE] = 0;
        config_index_[ConnectionType::READ] = 0;

        driver_ = dynamic_cast<sql::Driver*>(sql::mysql::get_driver_instance());
        connection_list_.reserve(options_.max_idle);
    }

protected:
    std::mutex mutex_;
    sql::Driver* driver_;
    std::unordered_map<ConnectionType, size_t> config_index_;
    std::unordered_map<ConnectionType, std::vector<sql::ConnectOptionsMap>> config_;
    std::vector<std::shared_ptr<sql::Connection>> connection_list_;

protected:
    Options options_;
};

}  // namespace ormxx::adaptor::mysql

#endif  // ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_H
