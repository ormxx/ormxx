#ifndef ORMXX_INTERFACE_RESULT_H
#define ORMXX_INTERFACE_RESULT_H

#include <string>

namespace ormxx {

class AdaptorResult {
public:
    virtual bool HasResult() const = 0;

    virtual bool ExecuteSuccess() const = 0;

    virtual int UpdatedRows() const = 0;

    virtual std::string ErrorMessage() const = 0;

    virtual bool Next() = 0;

    virtual bool IsNull(uint32_t column_index) const = 0;
    virtual bool IsNull(const std::string& column_label) const = 0;

    virtual bool GetBoolean(uint32_t column_index) const = 0;
    virtual bool GetBoolean(const std::string& column_label) const = 0;

    virtual int32_t GetInt(uint32_t column_index) const = 0;
    virtual int32_t GetInt(const std::string& column_label) const = 0;

    virtual uint32_t GetUInt(uint32_t column_index) const = 0;
    virtual uint32_t GetUInt(const std::string& column_label) const = 0;

    virtual int64_t GetInt64(uint32_t column_index) const = 0;
    virtual int64_t GetInt64(const std::string& column_label) const = 0;

    virtual uint64_t GetUInt64(uint32_t column_index) const = 0;
    virtual uint64_t GetUInt64(const std::string& column_label) const = 0;

    virtual long double GetDouble(uint32_t column_index) const = 0;
    virtual long double GetDouble(const std::string& column_label) const = 0;

    virtual std::string GetString(uint32_t column_index) const = 0;
    virtual std::string GetString(const std::string& column_label) const = 0;
};

}  // namespace ormxx

#endif  // ORMXX_INTERFACE_RESULT_H