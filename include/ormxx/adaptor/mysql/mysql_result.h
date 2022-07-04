#ifndef ORMXX_ADAPTOR_MYSQL_MYSQL_RESULT_H
#define ORMXX_ADAPTOR_MYSQL_MYSQL_RESULT_H

#include <string>
#include <type_traits>

#include "cppconn/resultset.h"

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

    bool IsNull(uint32_t column_index) const override {
        return result_set_->isNull(column_index);
    }

    bool IsNull(const std::string& column_label) const override {
        return result_set_->isNull(column_label);
    }

    bool GetBoolean(uint32_t column_index) const override {
        return result_set_->getBoolean(column_index);
    }

    bool GetBoolean(const std::string& column_label) const override {
        return result_set_->getBoolean(column_label);
    }

    void AssignColumn(bool& column, uint32_t column_index) const override {
        column = GetBoolean(column_index);
    }

    void AssignColumn(bool& column, const std::string& column_label) const override {
        column = GetBoolean(column_label);
    }

    int32_t GetInt(uint32_t column_index) const override {
        return result_set_->getInt(column_index);
    }

    int32_t GetInt(const std::string& column_label) const override {
        return result_set_->getInt(column_label);
    }

    void AssignColumn(int32_t& column, uint32_t column_index) const override {
        column = GetInt(column_index);
    }

    void AssignColumn(int32_t& column, const std::string& column_label) const override {
        column = GetInt(column_label);
    }

    uint32_t GetUInt(uint32_t column_index) const override {
        return result_set_->getUInt(column_index);
    }

    uint32_t GetUInt(const std::string& column_label) const override {
        return result_set_->getUInt(column_label);
    }

    void AssignColumn(uint32_t& column, uint32_t column_index) const override {
        column = GetUInt(column_index);
    }

    void AssignColumn(uint32_t& column, const std::string& column_label) const override {
        column = GetUInt(column_label);
    }

    int64_t GetInt64(uint32_t column_index) const override {
        return result_set_->getInt64(column_index);
    }

    int64_t GetInt64(const std::string& column_label) const override {
        return result_set_->getInt64(column_label);
    }

    void AssignColumn(int64_t& column, uint32_t column_index) const override {
        column = GetInt64(column_index);
    }

    void AssignColumn(int64_t& column, const std::string& column_label) const override {
        column = GetInt64(column_label);
    }

    uint64_t GetUInt64(uint32_t column_index) const override {
        return result_set_->getUInt64(column_index);
    }

    uint64_t GetUInt64(const std::string& column_label) const override {
        return result_set_->getUInt64(column_label);
    }

    void AssignColumn(uint64_t& column, uint32_t column_index) const override {
        column = GetUInt64(column_index);
    }

    void AssignColumn(uint64_t& column, const std::string& column_label) const override {
        column = GetUInt64(column_label);
    }

    long double GetDouble(uint32_t column_index) const override {
        return result_set_->getDouble(column_index);
    }

    long double GetDouble(const std::string& column_label) const override {
        return result_set_->getDouble(column_label);
    }

    void AssignColumn(long double& column, uint32_t column_index) const override {
        column = GetDouble(column_index);
    }

    void AssignColumn(long double& column, const std::string& column_label) const override {
        column = GetDouble(column_label);
    }

    std::string GetString(uint32_t column_index) const override {
        return result_set_->getString(column_index);
    }

    std::string GetString(const std::string& column_label) const override {
        return result_set_->getString(column_label);
    }

    void AssignColumn(std::string& column, uint32_t column_index) const override {
        column = GetString(column_index);
    }

    void AssignColumn(std::string& column, const std::string& column_label) const override {
        column = GetString(column_label);
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
