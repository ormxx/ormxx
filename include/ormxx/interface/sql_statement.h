#ifndef ORMXX_INTERFACE_SQL_STATEMENT_H
#define ORMXX_INTERFACE_SQL_STATEMENT_H

#include <string>
#include <variant>
#include <vector>

#include "../options/field_type.h"

namespace ormxx {

class SQLStatement {
public:
    struct Field {
        internal::FieldTypeStruct field_type;
        std::variant<bool, int32_t, uint32_t, int64_t, uint64_t, double, std::string> value;
    };

public:
    SQLStatement() {}
    SQLStatement(const std::string& sql, const std::vector<Field>& fields = {}) : sql_(sql), fields_(fields) {}
    virtual ~SQLStatement() {}

    void Append(const std::string& sql, const std::vector<Field>& fields = {}) {
        sql_ += sql;

        if (!fields.empty()) {
            fields_.insert(fields_.end(), fields.begin(), fields.end());
        }
    }

    void SetSQLString(const std::string& sql, const std::vector<Field>& fields = {}) {
        sql_ = sql;
        fields_ = fields;
    }

    const std::string& GetSQLString() const {
        return sql_;
    }

    const std::vector<Field>& GetFields() const {
        return fields_;
    }

private:
    std::string sql_{""};
    std::vector<Field> fields_{};
};

}  // namespace ormxx

#endif  // ORMXX_INTERFACE_SQL_STATEMENT_H
