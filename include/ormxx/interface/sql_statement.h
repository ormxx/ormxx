#ifndef ORMXX_INTERFACE_SQL_STATEMENT_H
#define ORMXX_INTERFACE_SQL_STATEMENT_H

#include <string>
#include <variant>
#include <vector>

#include "../options/field_type.h"

namespace ormxx {

class SQLStatement {
public:
    struct NullType {};

    using ValueType = std::variant<bool, int32_t, uint32_t, int64_t, uint64_t, double, std::string, NullType>;

    struct Field {
        internal::FieldTypeStruct field_type;
        ValueType value;
    };

public:
    SQLStatement() {}
    SQLStatement(const std::string& sql, const std::vector<Field>& fields = {}) : sql_(sql), fields_(fields) {}
    SQLStatement(std::string&& sql, std::vector<Field>&& fields = {})
            : sql_(std::move(sql)), fields_(std::move(fields)) {}
    virtual ~SQLStatement() {}

    void Append(const std::string& sql, const std::vector<Field>& fields = {}) {
        sql_ += sql;
        fields_.insert(fields_.end(), fields.begin(), fields.end());
    }

    void Append(std::string&& sql, std::vector<Field>&& fields = {}) {
        sql_ += std::move(sql);
        fields_.insert(fields_.end(), fields.begin(), fields.end());
    }

    void AppendSQLString(const std::string& sql) {
        sql_ += sql;
    }

    void AppendSQLString(std::string&& sql) {
        sql_ += std::move(sql);
    }

    void AppendField(const Field& field) {
        fields_.push_back(field);
    }

    void AppendField(Field&& field) {
        fields_.push_back(std::move(field));
    }

    void AppendFields(const std::vector<Field>& fields) {
        fields_.insert(fields_.end(), fields.begin(), fields.end());
    }

    void AppendFields(std::vector<Field>&& fields) {
        fields_.insert(fields_.end(), fields.begin(), fields.end());
    }

    void SetSQLString(const std::string& sql) {
        sql_ = sql;
    }

    void SetSQLString(std::string&& sql) {
        sql_ = std::move(sql);
    }

    void SetFields(const std::vector<Field>& fields) {
        fields_ = fields;
    }

    void SetFields(std::vector<Field>&& fields) {
        fields_ = std::move(fields);
    }

    const std::string& GetSQLString() const {
        return sql_;
    }

    const std::vector<Field>& GetFields() const {
        return fields_;
    }

    std::string& SQLString() {
        return sql_;
    }

    std::vector<Field>& Fields() {
        return fields_;
    }

private:
    std::string sql_{""};
    std::vector<Field> fields_{};
};

}  // namespace ormxx

#endif  // ORMXX_INTERFACE_SQL_STATEMENT_H
