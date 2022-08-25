#ifndef ORMXX_INTERNAL_FIELD_TO_SQL_STATEMENT_FIELD_VALUE_H
#define ORMXX_INTERNAL_FIELD_TO_SQL_STATEMENT_FIELD_VALUE_H

#include "../interface/index.h"

#include "../types_check/has_std_to_string.h"

namespace ormxx::internal {

template <typename T>
inline SQLStatement::ValueType FieldToSQLStatementFieldValue(const T* t) {
    return *t;
}

template <typename T>
inline SQLStatement::ValueType FieldToSQLStatementFieldValue(const std::optional<T>* t) {
    if (!t->has_value()) {
        return SQLStatement::NullType{};
    }

    return FieldToSQLStatementFieldValue(&t->value());
}

template <typename T>
inline std::string FieldToSQLStatementFieldValue(std::optional<T>* t) {
    return FieldToSQLStatementFieldValue(static_cast<const std::optional<T>*>(t));
}

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_FIELD_TO_SQL_STATEMENT_FIELD_VALUE_H
