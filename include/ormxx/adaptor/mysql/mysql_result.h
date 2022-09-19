#ifndef ORMXX_ADAPTOR_MYSQL_MYSQL_RESULT_H
#define ORMXX_ADAPTOR_MYSQL_MYSQL_RESULT_H

#include <string>
#include <type_traits>

#include "cppconn/resultset.h"
#include "fmt/core.h"

#include "../../interface/execute_result.h"

namespace ormxx::adaptor::mysql {

class MySQLResult : public ExecuteResult {
public:
    MySQLResult() = delete;

    MySQLResult(bool execute_success) : execute_success_(execute_success) {}

    MySQLResult(int rows_affected) : rows_affected_(rows_affected) {}

    MySQLResult(sql::ResultSet* result_set) : result_set_(result_set) {}

    ~MySQLResult() override {
        if (result_set_) {
            delete result_set_;
        }
    }

    MySQLResult(const MySQLResult&) = delete;
    void operator=(const MySQLResult&) = delete;

    MySQLResult(MySQLResult&& other) {
        move(std::move(other));
    }

    void operator=(MySQLResult&& other) {
        move(std::move(other));
    }

    bool ExecuteSuccess() const override {
        return execute_success_;
    }

    int RowsAffected() const override {
        return rows_affected_;
    }

    size_t RowsCount() const override {
        return result_set_->rowsCount();
    }

    sql::ResultSet* GetResultSet() {
        return result_set_;
    }

    bool Next() override {
        return result_set_->next();
    }

    ResultOr<bool> IsNull(uint32_t column_index) const override {
        try {
            return result_set_->isNull(column_index);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(
                                       fmt::format("IsNull failed. [column_index={}] [err={}]", column_index, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<bool> IsNull(const std::string& column_label) const override {
        try {
            return result_set_->isNull(column_label);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(
                                       fmt::format("IsNull failed. [column_label={}] [err={}]", column_label, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<bool> GetBoolean(uint32_t column_index) const override {
        try {
            return result_set_->getBoolean(column_index);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetBoolean failed. [column_index={}] [err={}]", column_index, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<bool> GetBoolean(const std::string& column_label) const override {
        try {
            return result_set_->getBoolean(column_label);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetBoolean failed. [column_label={}] [err={}]", column_label, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    Result AssignColumn(bool& column, uint32_t column_index) const override {
        RESULT_VALUE_OR_RETURN(column, GetBoolean(column_index));
        return Result::OK();
    }

    Result AssignColumn(bool& column, const std::string& column_label) const override {
        RESULT_VALUE_OR_RETURN(column, GetBoolean(column_label));
        return Result::OK();
    }

    ResultOr<int32_t> GetInt(uint32_t column_index) const override {
        try {
            return result_set_->getInt(column_index);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(
                                       fmt::format("GetInt failed. [column_index={}] [err={}]", column_index, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<int32_t> GetInt(const std::string& column_label) const override {
        try {
            return result_set_->getInt(column_label);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(
                                       fmt::format("GetInt failed. [column_label={}] [err={}]", column_label, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    Result AssignColumn(int32_t& column, uint32_t column_index) const override {
        RESULT_VALUE_OR_RETURN(column, GetInt(column_index));
        return Result::OK();
    }

    Result AssignColumn(int32_t& column, const std::string& column_label) const override {
        RESULT_VALUE_OR_RETURN(column, GetInt(column_label));
        return Result::OK();
    }

    ResultOr<uint32_t> GetUInt(uint32_t column_index) const override {
        try {
            return result_set_->getUInt(column_index);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetUInt failed. [column_index={}] [err={}]", column_index, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<uint32_t> GetUInt(const std::string& column_label) const override {
        try {
            return result_set_->getUInt(column_label);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetUInt failed. [column_label={}] [err={}]", column_label, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    Result AssignColumn(uint32_t& column, uint32_t column_index) const override {
        RESULT_VALUE_OR_RETURN(column, GetUInt(column_index));
        return Result::OK();
    }

    Result AssignColumn(uint32_t& column, const std::string& column_label) const override {
        RESULT_VALUE_OR_RETURN(column, GetUInt(column_label));
        return Result::OK();
    }

    ResultOr<int64_t> GetInt64(uint32_t column_index) const override {
        try {
            return result_set_->getInt64(column_index);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetInt64 failed. [column_index={}] [err={}]", column_index, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<int64_t> GetInt64(const std::string& column_label) const override {
        try {
            return result_set_->getInt64(column_label);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(
                                       fmt::format("GetInt64. [column_label={}], [err={}]", column_label, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    Result AssignColumn(int64_t& column, uint32_t column_index) const override {
        RESULT_VALUE_OR_RETURN(column, GetInt64(column_index));
        return Result::OK();
    }

    Result AssignColumn(int64_t& column, const std::string& column_label) const override {
        RESULT_VALUE_OR_RETURN(column, GetInt64(column_label));
        return Result::OK();
    }

    ResultOr<uint64_t> GetUInt64(uint32_t column_index) const override {
        try {
            return result_set_->getUInt64(column_index);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetUInt64 failed. [column_index={}] [err={}]", column_index, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<uint64_t> GetUInt64(const std::string& column_label) const override {
        try {
            return result_set_->getUInt64(column_label);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetUInt64 failed. [column_label={}] [err={}]", column_label, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    Result AssignColumn(uint64_t& column, uint32_t column_index) const override {
        RESULT_VALUE_OR_RETURN(column, GetUInt64(column_index));
        return Result::OK();
    }

    Result AssignColumn(uint64_t& column, const std::string& column_label) const override {
        RESULT_VALUE_OR_RETURN(column, GetUInt64(column_label));
        return Result::OK();
    }

    ResultOr<long double> GetDouble(uint32_t column_index) const override {
        try {
            return result_set_->getDouble(column_index);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetDouble failed. [column_index={}] [err={}]", column_index, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<long double> GetDouble(const std::string& column_label) const override {
        try {
            return result_set_->getDouble(column_label);
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetDouble failed. [column_label={}] [err={}]", column_label, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    Result AssignColumn(long double& column, uint32_t column_index) const override {
        RESULT_VALUE_OR_RETURN(column, GetDouble(column_index));
        return Result::OK();
    }

    Result AssignColumn(long double& column, const std::string& column_label) const override {
        RESULT_VALUE_OR_RETURN(column, GetDouble(column_label));
        return Result::OK();
    }

    ResultOr<std::string> GetString(uint32_t column_index) const override {
        try {
            return std::string(result_set_->getString(column_index));
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetString failed. [column_index={}] [err={}]", column_index, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    ResultOr<std::string> GetString(const std::string& column_label) const override {
        try {
            return std::string(result_set_->getString(column_label));
        } catch (std::exception& e) {
            auto res = Result::Builder(Result::ErrorCode::GetColumnValueError)
                               .WithErrorMessage(fmt::format(
                                       "GetString failed. [column_label={}] [err={}]", column_label, e.what()))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }
    }

    Result AssignColumn(std::string& column, uint32_t column_index) const override {
        RESULT_VALUE_OR_RETURN(column, GetString(column_index));
        return Result::OK();
    }

    Result AssignColumn(std::string& column, const std::string& column_label) const override {
        RESULT_VALUE_OR_RETURN(column, GetString(column_label));
        return Result::OK();
    }

private:
    void move(MySQLResult&& other) {
        execute_success_ = other.execute_success_;
        rows_affected_ = other.rows_affected_;
        result_set_ = other.result_set_;

        other.result_set_ = nullptr;
    }

private:
    bool execute_success_{false};
    int rows_affected_{0};
    sql::ResultSet* result_set_{nullptr};
};

}  // namespace ormxx::adaptor::mysql

#endif  // ORMXX_ADAPTOR_MYSQL_MYSQL_RESULT_H
