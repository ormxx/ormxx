#ifndef ORMXX_ADAPTOR_MYSQL_MYSQL_RESULT_H
#define ORMXX_ADAPTOR_MYSQL_MYSQL_RESULT_H

#include <string>
#include <type_traits>

#include "cppconn/resultset.h"

#include "../../interface/adaptor_result.h"

namespace ormxx::adaptor::mysql {

class MySQLResult : public AdaptorResult {
public:
    MySQLResult() = delete;

    MySQLResult(bool execute_success) : has_result_(true), execute_success_(execute_success) {}

    MySQLResult(int updated_rows) : has_result_(true), updated_rows_(updated_rows) {}

    MySQLResult(sql::ResultSet* result_set) : has_result_(true), result_set_(result_set) {}

    MySQLResult(const std::string& error_message) : error_message_(error_message) {}

    ~MySQLResult() {
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

    bool HasResult() const override {
        return has_result_;
    }

    bool ExecuteSuccess() const override {
        return execute_success_;
    }

    int UpdatedRows() const override {
        return updated_rows_;
    }

    sql::ResultSet* GetResultSet() {
        return result_set_;
    }

    std::string ErrorMessage() const override {
        return error_message_;
    }

    size_t RowsCount() const {
        return result_set_->rowsCount();
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

    int32_t GetInt(uint32_t column_index) const override {
        return result_set_->getInt(column_index);
    }

    int32_t GetInt(const std::string& column_label) const override {
        return result_set_->getInt(column_label);
    }

    uint32_t GetUInt(uint32_t column_index) const override {
        return result_set_->getUInt(column_index);
    }

    uint32_t GetUInt(const std::string& column_label) const override {
        return result_set_->getUInt(column_label);
    }

    int64_t GetInt64(uint32_t column_index) const override {
        return result_set_->getInt64(column_index);
    }

    int64_t GetInt64(const std::string& column_label) const override {
        return result_set_->getInt64(column_label);
    }

    uint64_t GetUInt64(uint32_t column_index) const override {
        return result_set_->getUInt64(column_index);
    }

    uint64_t GetUInt64(const std::string& column_label) const override {
        return result_set_->getUInt64(column_label);
    }

    long double GetDouble(uint32_t column_index) const override {
        return result_set_->getDouble(column_index);
    }

    long double GetDouble(const std::string& column_label) const override {
        return result_set_->getDouble(column_label);
    }

    std::string GetString(uint32_t column_index) const override {
        return result_set_->getString(column_index);
    }

    std::string GetString(const std::string& column_label) const override {
        return result_set_->getString(column_label);
    }

    template <typename T>
    T GetColumn(uint32_t column_index) const {
        if constexpr (std::is_same_v<bool, T>) {
            return result_set_->getBoolean(column_index);
        }

        if constexpr (std::is_same_v<int32_t, T>) {
            return result_set_->getInt(column_index);
        }

        if constexpr (std::is_same_v<uint32_t, T>) {
            return result_set_->getUInt(column_index);
        }

        if constexpr (std::is_same_v<int64_t, T>) {
            return result_set_->getInt64(column_index);
        }

        if constexpr (std::is_same_v<uint64_t, T>) {
            return result_set_->getUInt64(column_index);
        }

        if constexpr (std::is_same_v<long double, T>) {
            return result_set_->getDouble(column_index);
        }

        if constexpr (std::is_same_v<std::string, T>) {
            return result_set_->getString(column_index);
        }
    }

    template <typename T>
    T GetColumn(const std::string& column_label) const {
        if constexpr (std::is_same_v<bool, T>) {
            return result_set_->getBoolean(column_label);
        }

        if constexpr (std::is_same_v<int32_t, T>) {
            return result_set_->getInt(column_label);
        }

        if constexpr (std::is_same_v<uint32_t, T>) {
            return result_set_->getUInt(column_label);
        }

        if constexpr (std::is_same_v<int64_t, T>) {
            return result_set_->getInt64(column_label);
        }

        if constexpr (std::is_same_v<uint64_t, T>) {
            return result_set_->getUInt64(column_label);
        }

        if constexpr (std::is_same_v<long double, T>) {
            return result_set_->getDouble(column_label);
        }

        if constexpr (std::is_same_v<std::string, T>) {
            return result_set_->getString(column_label);
        }
    }

    template <typename T>
    void AssignColumnToVar(T& column, uint32_t column_index) const {
        column = GetColumn<T>(column_index);
    }

    template <typename T>
    void AssignColumnToVar(T& column, const std::string& column_label) const {
        column = GetColumn<T>(column_label);
    }

private:
    void move(MySQLResult&& other) {
        has_result_ = other.has_result_;
        execute_success_ = other.execute_success_;
        updated_rows_ = other.updated_rows_;
        result_set_ = other.result_set_;
        error_message_ = other.error_message_;

        other.result_set_ = nullptr;
    }

private:
    bool has_result_{false};
    bool execute_success_{false};
    int updated_rows_{0};
    sql::ResultSet* result_set_{nullptr};
    std::string error_message_;
};

}  // namespace ormxx::adaptor::mysql

#endif  // ORMXX_ADAPTOR_MYSQL_MYSQL_RESULT_H
