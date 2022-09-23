#ifndef ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_H
#define ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_H

#include <atomic>
#include <cstddef>
#include <functional>
#include <memory>

#include "cppconn/connection.h"
#include "cppconn/prepared_statement.h"
#include "fmt/core.h"

#include "../../interface/connection.h"
#include "../../interface/execute_result.h"

#include "./mysql_result.h"

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
            is_closed = true;

            try {
                connection_->close();
            } catch (...) {
            }

            delete connection_;
            connection_ = nullptr;
        }
    }

    bool IsClosed() override {
        return is_closed;
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

    ResultOr<std::unique_ptr<ExecuteResult>> Execute(const SQLStatement& sql_statement, const std::string& schema) {
        try {
            if (!schema.empty()) {
                connection_->setSchema(schema);
            }

            std::unique_ptr<sql::PreparedStatement> statement(
                    connection_->prepareStatement(sql_statement.GetSQLString()));
            RESULT_VALUE_OR_RETURN(statement, fillStatementField(std::move(statement), sql_statement));

            bool execute_success = statement->execute();

            auto res = std::unique_ptr<ExecuteResult>(nullptr);
            res.reset(dynamic_cast<ExecuteResult*>(new MySQLResult(execute_success)));
            return res;
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::ExecuteError)
                               .WithErrorMessage(fmt::format("MySQL Execute failed. [err={}] [sql={}] [fields={}]",
                                                             e.what(),
                                                             sql_statement.GetSQLString(),
                                                             sql_statement.FieldsToString()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<std::unique_ptr<ExecuteResult>> Execute(const std::string& sql, const std::string& schema) {
        auto sql_statement = SQLStatement(sql);
        RESULT_DIRECT_RETURN(Execute(sql_statement, schema));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> Execute(const SQLStatement& sql_statement) override {
        RESULT_DIRECT_RETURN(Execute(sql_statement, schema_));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> Execute(const std::string& sql) override {
        RESULT_DIRECT_RETURN(Execute(sql, schema_));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const SQLStatement& sql_statement,
                                                          const std::string& schema) {
        try {
            if (!schema.empty()) {
                connection_->setSchema(schema);
            }

            std::unique_ptr<sql::PreparedStatement> statement(
                    connection_->prepareStatement(sql_statement.GetSQLString()));
            RESULT_VALUE_OR_RETURN(statement, fillStatementField(std::move(statement), sql_statement));

            auto* result_set = statement->executeQuery();

            auto res = std::unique_ptr<ExecuteResult>(nullptr);
            res.reset(dynamic_cast<ExecuteResult*>(new MySQLResult(result_set)));
            return res;
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::ExecuteError)
                               .WithErrorMessage(fmt::format("MySQL ExecuteQuery failed. [err={}] [sql={}] [fields={}]",
                                                             e.what(),
                                                             sql_statement.GetSQLString(),
                                                             sql_statement.FieldsToString()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const std::string& sql, const std::string& schema) {
        auto sql_statement = SQLStatement(sql);
        RESULT_DIRECT_RETURN(ExecuteQuery(sql_statement, schema));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const SQLStatement& sql_statement) override {
        RESULT_DIRECT_RETURN(ExecuteQuery(sql_statement, schema_));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const std::string& sql) override {
        RESULT_DIRECT_RETURN(ExecuteQuery(sql, schema_));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const SQLStatement& sql_statement,
                                                           const std::string& schema) {
        try {
            if (!schema.empty()) {
                connection_->setSchema(schema);
            }

            std::unique_ptr<sql::PreparedStatement> statement(
                    connection_->prepareStatement(sql_statement.GetSQLString()));
            RESULT_VALUE_OR_RETURN(statement, fillStatementField(std::move(statement), sql_statement));

            int rows_affected = statement->executeUpdate();

            auto res = std::unique_ptr<ExecuteResult>(nullptr);
            res.reset(dynamic_cast<ExecuteResult*>(new MySQLResult(rows_affected)));
            return res;
        } catch (std::exception& e) {
            auto res =
                    Result::Builder(Result::ErrorCode::ExecuteError)
                            .WithErrorMessage(fmt::format("MySQL ExecuteUpdate failed. [err={}] [sql={}] [fields={}]",
                                                          e.what(),
                                                          sql_statement.GetSQLString(),
                                                          sql_statement.FieldsToString()))
                            .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const std::string& sql, const std::string& schema) {
        auto sql_statement = SQLStatement(sql);
        RESULT_DIRECT_RETURN(ExecuteUpdate(sql_statement, schema));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const SQLStatement& sql_statement) override {
        RESULT_DIRECT_RETURN(ExecuteUpdate(sql_statement, schema_));
    }

    ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const std::string& sql) override {
        RESULT_DIRECT_RETURN(ExecuteUpdate(sql, schema_));
    }

private:
    ResultOr<std::unique_ptr<sql::PreparedStatement>> fillStatementField(
            std::unique_ptr<sql::PreparedStatement> statement, const SQLStatement& sql_statement) {
        using CXXFieldType = internal::CXXFieldType;

        const auto& fields = sql_statement.GetFields();

        for (size_t i = 1; i <= fields.size(); ++i) {
            const auto& field = fields[i - 1];
            const auto& t = field.field_type.cxx_field_type;

            if (std::holds_alternative<SQLStatement::NullType>(field.value)) {
                // `sqlType` is not used in the mysql-connector-cpp implementation
                statement->setNull(i, 0);
                continue;
            }

            if (t == CXXFieldType::BOOLEAN) {
                statement->setBoolean(i, std::get<bool>(field.value));
            } else if (t == CXXFieldType::INT) {
                statement->setInt(i, std::get<int32_t>(field.value));
            } else if (t == CXXFieldType::UINT) {
                statement->setUInt(i, std::get<uint32_t>(field.value));
            } else if (t == CXXFieldType::INT64) {
                statement->setInt64(i, std::get<int64_t>(field.value));
            } else if (t == CXXFieldType::UINT64) {
                statement->setUInt64(i, std::get<uint64_t>(field.value));
            } else if (t == CXXFieldType::DOUBLE) {
                statement->setDouble(i, std::get<double>(field.value));
            } else if (t == CXXFieldType::STRING) {
                statement->setString(i, std::get<std::string>(field.value));
            } else {
                auto res = Result::Builder(Result::ErrorCode::UnSupportTypeError)
                                   .WithErrorMessage("unsupported type with unknown type field")
                                   .Build();
                RESULT_DIRECT_RETURN(res);
            }
        }

        return statement;
    }

private:
    std::string schema_{""};
    sql::Connection* connection_{nullptr};
    std::atomic_bool is_closed{false};

    inline static thread_local bool pre_auto_commit_value = true;
};

}  // namespace ormxx::adaptor::mysql

#endif  // ORMXX_ADAPTOR_MYSQL_MYSQL_CONNECTION_H
