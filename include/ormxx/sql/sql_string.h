#ifndef ORMXX_SQL_SQL_STRING_H
#define ORMXX_SQL_SQL_STRING_H

#include <string>
#include <variant>
#include <vector>

#include "../options/field_type.h"

namespace ormxx {

class SQLString {
public:
    struct Field {
        internal::FieldTypeStruct field_type;
        std::variant<bool, int32_t, uint32_t, int64_t, uint64_t, double, std::string> value;
    };

    void Append(const std::string& sql, const std::vector<Field>& fields = {}) {
        sql_ += sql;

        if (!fields.empty()) {
            fields_.insert(fields_.end(), fields.begin(), fields.end());
        }
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

#endif  // ORMXX_SQL_SQL_STRING_H
