#ifndef ORMXX_INTERFACE_EXECUTE_RESULT_H
#define ORMXX_INTERFACE_EXECUTE_RESULT_H

#include <string>

#include "./result.h"

namespace ormxx {

class ExecuteResult {
public:
    ExecuteResult() {}
    virtual ~ExecuteResult() {}

    virtual bool ExecuteSuccess() const = 0;

    virtual int RowsAffected() const = 0;

    virtual size_t RowsCount() const = 0;

    virtual bool Next() = 0;

    virtual ResultOr<bool> IsNull(uint32_t column_index) const = 0;
    virtual ResultOr<bool> IsNull(const std::string& column_label) const = 0;

    virtual ResultOr<bool> GetBoolean(uint32_t column_index) const = 0;
    virtual ResultOr<bool> GetBoolean(const std::string& column_label) const = 0;
    virtual Result AssignColumn(bool& column, uint32_t column_index) const = 0;
    virtual Result AssignColumn(bool& column, const std::string& column_label) const = 0;

    virtual ResultOr<int32_t> GetInt(uint32_t column_index) const = 0;
    virtual ResultOr<int32_t> GetInt(const std::string& column_label) const = 0;
    virtual Result AssignColumn(int32_t& column, uint32_t column_index) const = 0;
    virtual Result AssignColumn(int32_t& column, const std::string& column_label) const = 0;

    virtual ResultOr<uint32_t> GetUInt(uint32_t column_index) const = 0;
    virtual ResultOr<uint32_t> GetUInt(const std::string& column_label) const = 0;
    virtual Result AssignColumn(uint32_t& column, uint32_t column_index) const = 0;
    virtual Result AssignColumn(uint32_t& column, const std::string& column_label) const = 0;

    virtual ResultOr<int64_t> GetInt64(uint32_t column_index) const = 0;
    virtual ResultOr<int64_t> GetInt64(const std::string& column_label) const = 0;
    virtual Result AssignColumn(int64_t& column, uint32_t column_index) const = 0;
    virtual Result AssignColumn(int64_t& column, const std::string& column_label) const = 0;

    virtual ResultOr<uint64_t> GetUInt64(uint32_t column_index) const = 0;
    virtual ResultOr<uint64_t> GetUInt64(const std::string& column_label) const = 0;
    virtual Result AssignColumn(uint64_t& column, uint32_t column_index) const = 0;
    virtual Result AssignColumn(uint64_t& column, const std::string& column_label) const = 0;

    virtual ResultOr<long double> GetDouble(uint32_t column_index) const = 0;
    virtual ResultOr<long double> GetDouble(const std::string& column_label) const = 0;
    virtual Result AssignColumn(long double& column, uint32_t column_index) const = 0;
    virtual Result AssignColumn(long double& column, const std::string& column_label) const = 0;

    virtual ResultOr<std::string> GetString(uint32_t column_index) const = 0;
    virtual ResultOr<std::string> GetString(const std::string& column_label) const = 0;
    virtual Result AssignColumn(std::string& column, uint32_t column_index) const = 0;
    virtual Result AssignColumn(std::string& column, const std::string& column_label) const = 0;
};

}  // namespace ormxx

#endif  // ORMXX_INTERFACE_EXECUTE_RESULT_H
