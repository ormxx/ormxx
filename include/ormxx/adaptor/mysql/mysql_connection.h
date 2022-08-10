#ifndef ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_H
#define ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_H

#include <cstddef>
#include <functional>
#include <memory>

#include "cppconn/connection.h"
#include "cppconn/prepared_statement.h"
#include "fmt/core.h"

#include "../../interface/connection.h"
#include "../../interface/execute_result.h"

#include "./mysql_result.h"
#include "result/macros.h"

namespace ormxx::adaptor::mysql {

class MySQLConnection : public Connection {
public:
    MySQLConnection() = delete;
    MySQLConnection(sql::Connection* connection) : connection_(connection) {}

    ~MySQLConnection() override {
        Close();
    }

    MySQLConnection& SetSchema(const std::string& schema) {
        schema_ = schema;
        return *this;
    }

    sql::Connection* GetConnection() {
        return connection_;
    }

    bool ReConnect() override {
        if (connection_) {
            try {
                return connection_->reconnect();
            } catch (...) {
                return false;
            }
        }

        return false;
    }

    void Close() override {
        if (connection_) {
            try {
                connection_->close();
            } catch (...) {
            }

            delete connection_;
            connection_ = nullptr;
        }
    }

    Result BeginTransaction() override {
        try {
            pre_auto_commit_value = connection_->getAutoCommit();
            connection_->setAutoCommit(false);
            return Result::OK();
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::ExecuteError)
                               .WithErrorMessage(fmt::format("MySQL Begin Transaction failed. [err={}]", e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    Result Commit() override {
        try {
            connection_->commit();
            connection_->setAutoCommit(pre_auto_commit_value);
            return Result::OK();
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::ExecuteError)
                               .WithErrorMessage(fmt::format("MySQL Commit failed. [err={}]", e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    Result Rollback() override {
        try {
            connection_->rollback();
            connection_->setAutoCommit(pre_auto_commit_value);
            return Result::OK();
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::ExecuteError)
                               .WithErrorMessage(fmt::format("MySQL Rollback failed. [err={}]", e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<std::unique_ptr<ExecuteResult>> Execute(const std::string& sql, const std::string& schema) {
        try {
            if (!schema.empty()) {
                connection_->setSchema(schema);
            }

            std::unique_ptr<sql::PreparedStatement> statement(connection_->prepareStatement(sql));
            bool execute_success = statement->execute();

            auto res = std::unique_ptr<ExecuteResult>(nullptr);
            res.reset(dynamic_cast<ExecuteResult*>(new MySQLResult(execute_success)));
            return res;
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::ExecuteError)
                               .WithErrorMessage(fmt::format("MySQL Execute failed. [err={}] [sql={}]", e.what(), sql))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<std::unique_ptr<ExecuteResult>> Execute(const std::string& sql) override {
        RESULT_DIRECT_RETURN(Execute(sql, schema_));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const std::string& sql, const std::string& schema) {
        try {
            if (!schema.empty()) {
                connection_->setSchema(schema);
            }

            std::unique_ptr<sql::PreparedStatement> statement(connection_->prepareStatement(sql));
            auto* result_set = statement->executeQuery();

            auto res = std::unique_ptr<ExecuteResult>(nullptr);
            res.reset(dynamic_cast<ExecuteResult*>(new MySQLResult(result_set)));
            return res;
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::ExecuteError)
                               .WithErrorMessage(
                                       fmt::format("MySQL ExecuteQuery failed. [err={}] [sql={}]", e.what(), sql))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const std::string& sql) override {
        RESULT_DIRECT_RETURN(ExecuteQuery(sql, schema_));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const std::string& sql, const std::string& schema) {
        try {
            if (!schema.empty()) {
                connection_->setSchema(schema);
            }

            std::unique_ptr<sql::PreparedStatement> statement(connection_->prepareStatement(sql));
            int rows_affected = statement->executeUpdate();

            auto res = std::unique_ptr<ExecuteResult>(nullptr);
            res.reset(dynamic_cast<ExecuteResult*>(new MySQLResult(rows_affected)));
            return res;
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::ExecuteError)
                               .WithErrorMessage(
                                       fmt::format("MySQL ExecuteUpdate failed. [err={}] [sql={}]", e.what(), sql))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const std::string& sql) override {
        RESULT_DIRECT_RETURN(ExecuteUpdate(sql, schema_));
    }

private:
    std::string schema_{""};
    sql::Connection* connection_{nullptr};

    inline static thread_local bool pre_auto_commit_value = true;
};

}  // namespace ormxx::adaptor::mysql

#endif  // ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_H
