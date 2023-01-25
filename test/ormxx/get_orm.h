#pragma once

#include <functional>
#include <memory>

#include "ormxx/adaptor/mysql/mysql_adaptor.h"

#include "ormxx/ormxx.h"

namespace ormxx::test {

inline ORMXX* GetORMXX() {
    static ORMXX* orm = std::invoke([]() {
        const char* hostname = std::getenv("MYSQL_HOSTNAME");
        const char* port = std::getenv("MYSQL_PORT");
        const char* username = std::getenv("MYSQL_USERNAME");
        const char* password = std::getenv("MYSQL_PASSWORD");
        const char* schema = std::getenv("MYSQL_SCHEMA");

        if (hostname == nullptr) {
            hostname = "127.0.0.1";
        }

        if (port == nullptr) {
            port = "3306";
        }

        if (username == nullptr) {
            username = "root";
        }

        if (password == nullptr) {
            password = "password";
        }

        if (schema == nullptr) {
            schema = "mysqlclient_unittest";
        }

        auto config = adaptor::mysql::MySQLConfig::Builder()
                              .WithHostname(hostname)
                              .WithPort(port ? std::stoi(port) : 3306)
                              .WithUsername(username)
                              .WithPassword(password)
                              .WithSchema(schema)
                              .Build();

        auto* mysql_adaptor = new adaptor::mysql::MySQLAdaptor();
        mysql_adaptor->AddWriteConfig(config);

        return ORMXX::Builder(dynamic_cast<Adaptor*>(mysql_adaptor)).BuildPtr();
    });

    return orm;
}

}  // namespace ormxx::test
