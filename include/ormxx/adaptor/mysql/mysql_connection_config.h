#ifndef ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_CONFIG_H
#define ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_CONFIG_H

#include <cstdint>
#include <string>

#include "cppconn/connection.h"

namespace ormxx::adaptor::mysql {

class MySQLConnectionConfig {
public:
    struct Options {
        std::string hostname;
        int port{-1};
        std::string username;
        std::string password;
        std::string schema;

        bool re_connect{true};
        int connect_timeout{5};
        int read_timeout{5};
        int write_timeout{5};
    };

    class Builder {
    public:
        Builder& WithHostname(const std::string& hostname) {
            options_.hostname = hostname;
            return *this;
        }

        Builder& WithPort(int port) {
            options_.port = port;
            return *this;
        }

        Builder& WithUsername(const std::string& username) {
            options_.username = username;
            return *this;
        }

        Builder& WithPassword(const std::string& password) {
            options_.password = password;
            return *this;
        }

        Builder& WithSchema(const std::string& schema) {
            options_.schema = schema;
            return *this;
        }

        Builder& WithReConnect(bool re_connect) {
            options_.re_connect = re_connect;
            return *this;
        }

        Builder& WithConnectTimeout(int connect_timeout) {
            options_.connect_timeout = connect_timeout;
            return *this;
        }

        Builder& WithReadTimeout(int read_timeout) {
            options_.read_timeout = read_timeout;
            return *this;
        }

        Builder& WithWriteTimeout(int write_timeout) {
            options_.write_timeout = write_timeout;
            return *this;
        }

        MySQLConnectionConfig Build() {
            return MySQLConnectionConfig(options_);
        }

        MySQLConnectionConfig* BuildPtr() {
            return new MySQLConnectionConfig(options_);
        }

    private:
        Options options_;
    };

public:
    MySQLConnectionConfig() = delete;

    MySQLConnectionConfig(const Options& options) : options_(options) {
        init();
    }

    ~MySQLConnectionConfig() {}

    sql::ConnectOptionsMap GetConnectOptionsMap() const {
        return connect_options_map_;
    }

private:
    void init() {
        if (!options_.hostname.empty()) {
            connect_options_map_["hostName"] = sql::ConnectPropertyVal(options_.hostname);
        }

        if (!options_.username.empty()) {
            connect_options_map_["userName"] = sql::ConnectPropertyVal(options_.username);
        }

        if (options_.port != -1) {
            connect_options_map_["port"] = sql::ConnectPropertyVal(options_.port);
        }

        if (!options_.password.empty()) {
            connect_options_map_["password"] = sql::ConnectPropertyVal(options_.password);
        }

        if (!options_.schema.empty()) {
            connect_options_map_["schema"] = sql::ConnectPropertyVal(options_.schema);
        }

        connect_options_map_["OPT_RECONNECT"] = sql::ConnectPropertyVal(options_.re_connect);
        connect_options_map_["OPT_CONNECT_TIMEOUT"] = sql::ConnectPropertyVal(options_.connect_timeout);
        connect_options_map_["OPT_READ_TIMEOUT"] = sql::ConnectPropertyVal(options_.read_timeout);
        connect_options_map_["OPT_WRITE_TIMEOUT"] = sql::ConnectPropertyVal(options_.write_timeout);
    }

private:
    sql::ConnectOptionsMap connect_options_map_{};

    Options options_;
};

}  // namespace ormxx::adaptor::mysql

#endif  // ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_CONFIG_H
