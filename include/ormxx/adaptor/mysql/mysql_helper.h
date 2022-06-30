#ifndef ORMXX_ADAPTOR_MYSQL_MYSQL_HELPER_H
#define ORMXX_ADAPTOR_MYSQL_MYSQL_HELPER_H

#include <functional>

#include "cppconn/connection.h"
#include "cppconn/prepared_statement.h"
#include "fmt/core.h"

#include "./mysql_result.h"

namespace ormxx::adaptor::mysql {

class MySQLHelper {
public:
    MySQLHelper() = delete;
    MySQLHelper(std::shared_ptr<sql::Connection> connection, std::function<void()> release_connection)
            : connection_(connection), release_connection_(release_connection) {}

    ~MySQLHelper() {
        if (release_connection_) {
            release_connection_();
        }
    }

    MySQLHelper& SetSchema(const std::string& schema) {
        schema_ = schema;
        return *this;
    }

    std::shared_ptr<sql::Connection> GetConnection() {
        return connection_;
    }

    MySQLResult Execute(const std::string& sql, const std::string& schema) {
        try {
            if (!schema.empty()) {
                connection_->setSchema(schema);
            }

            std::unique_ptr<sql::PreparedStatement> statement(connection_->prepareStatement(sql));
            bool execute_success = statement->execute();
            return MySQLResult(execute_success);
        } catch (std::exception& e) {
            return MySQLResult(fmt::format("MySQL Execute failed. [err={}, sql={}]", e.what(), sql));
        }
    }

    MySQLResult Execute(const std::string& sql) {
        return Execute(sql, schema_);
    }

    MySQLResult ExecuteQuery(const std::string& sql, const std::string& schema) {
        try {
            if (!schema.empty()) {
                connection_->setSchema(schema);
            }

            std::unique_ptr<sql::PreparedStatement> statement(connection_->prepareStatement(sql));
            auto* result_set = statement->executeQuery();
            return MySQLResult(result_set);
        } catch (std::exception& e) {
            return MySQLResult(fmt::format("MySQL ExecuteQuery failed. [err={}, sql={}]", e.what(), sql));
        }
    }

    MySQLResult ExecuteQuery(const std::string& sql) {
        return ExecuteQuery(sql, schema_);
    }

    MySQLResult ExecuteUpdate(const std::string& sql, const std::string& schema) {
        try {
            if (!schema.empty()) {
                connection_->setSchema(schema);
            }

            std::unique_ptr<sql::PreparedStatement> statement(connection_->prepareStatement(sql));
            int updated_rows_ = statement->executeUpdate();
            return MySQLResult(updated_rows_);
        } catch (std::exception& e) {
            return MySQLResult(fmt::format("MySQL ExecuteUpdate failed. [err={}, sql={}]", e.what(), sql));
        }
    }

    MySQLResult ExecuteUpdate(const std::string& sql) {
        return ExecuteUpdate(sql, schema_);
    }

private:
    std::string schema_{""};
    std::shared_ptr<sql::Connection> connection_{nullptr};
    std::function<void()> release_connection_{nullptr};
};

}  // namespace ormxx::adaptor::mysql

#endif  // ORMXX_ADAPTOR_MYSQL_MYSQL_HELPER_H
