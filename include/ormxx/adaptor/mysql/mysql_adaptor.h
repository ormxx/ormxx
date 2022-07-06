#ifndef ORMXX_ADAPTOR_MYSQL_MYSQL_ADAPTOR_H
#define ORMXX_ADAPTOR_MYSQL_MYSQL_ADAPTOR_H

#include <unordered_map>
#include <vector>

#include "cppconn/connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "fmt/core.h"
#include "mysql_connection.h"
#include "mysql_driver.h"

#include "../../interface/adaptor.h"
#include "../../interface/result.h"

#include "./mysql_config.h"      // IWYU pragma: export
#include "./mysql_connection.h"  // IWYU pragma: export
#include "./mysql_result.h"      // IWYU pragma: export

namespace ormxx::adaptor::mysql {

class MySQLAdaptor : public Adaptor {
public:
    MySQLAdaptor() {
        driver_ = dynamic_cast<sql::Driver*>(sql::mysql::get_driver_instance());
    }

    ~MySQLAdaptor() override {}

    MySQLAdaptor& AddConfig(const MySQLConfig& config, ConnectionType connection_type = ConnectionType::WRITE) {
        config_map_[connection_type].push_back(config);
        return *this;
    }

    MySQLAdaptor& AddWriteConfig(const MySQLConfig& config) {
        return AddConfig(config, ConnectionType::WRITE);
    }

    MySQLAdaptor& AddReadConfig(const MySQLConfig& config) {
        return AddConfig(config, ConnectionType::READ);
    }

    bool HasConfig(ConnectionType connection_type = ConnectionType::WRITE) const {
        auto check = [this](ConnectionType connection_type) {
            return config_map_.count(connection_type) != 0 && !config_map_.at(connection_type).empty();
        };

        if (connection_type == ConnectionType::WRITE) {
            return check(ConnectionType::WRITE);
        }

        if (connection_type == ConnectionType::READ) {
            return check(ConnectionType::READ) || check(ConnectionType::WRITE);
        }

        return false;
    }

    bool HasWriteConfig() const {
        return HasConfig(ConnectionType::WRITE);
    }

    bool HasReadConfig() const {
        return HasConfig(ConnectionType::READ);
    }

    ResultOr<Connection*> GetConnection(ConnectionType type = ConnectionType::WRITE) override {
        if (!HasConfig(type)) {
            return Result::Builder(Result::ErrorCode::ConnectionError)
                    .WithErrorMessage(fmt::format("No config found. [connection type={}]",
                                                  type == ConnectionType::WRITE ? "WRITE" : "READ"))
                    .Build();
        }

        try {
            auto config = getConfig(type).GetConnectOptionsMap();
            auto* conn = driver_->connect(config);
            return dynamic_cast<Connection*>(new MySQLConnection(conn));
        } catch (std::exception& e) {
            return Result::Builder(Result::ErrorCode::ConnectionError)
                    .WithErrorMessage(fmt::format("Failed to get connection. [error={}]", e.what()))
                    .Build();
        }
    }

private:
    // maybe core dump
    MySQLConfig getConfig(ConnectionType connection_type = ConnectionType::WRITE) const {
        if (connection_type == ConnectionType::READ) {
            if (config_map_.count(ConnectionType::READ) != 0 && !config_map_.at(ConnectionType::READ).empty()) {
                return config_map_.at(ConnectionType::READ).front();
            }
        }

        return config_map_.at(ConnectionType::WRITE).front();
    }

private:
    sql::Driver* driver_;
    std::unordered_map<ConnectionType, std::vector<MySQLConfig>> config_map_;
};

}  // namespace ormxx::adaptor::mysql

#endif  // ORMXX_ADAPTOR_MYSQL_MYSQL_ADAPTOR_H
