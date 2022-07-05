#pragma once

#include <functional>
#include <memory>

#include "ormxx/adaptor/mysql/mysql_adaptor.h"

#include "ormxx/ormxx.h"

namespace ormxx::test {

inline ORMXX* GetORMXX() {
    static ORMXX* orm = std::invoke([]() {
        auto* hostname = std::getenv("MYSQL_HOSTNAME");
        auto* port = std::getenv("MYSQL_PORT");
        auto* username = std::getenv("MYSQL_USERNAME");
        auto* password = std::getenv("MYSQL_PASSWORD");
        auto* schema = std::getenv("MYSQL_SCHEMA");

        assert(hostname != nullptr);
        assert(username != nullptr);
        assert(password != nullptr);
        assert(schema != nullptr);

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
