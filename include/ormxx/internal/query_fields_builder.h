#ifndef ORMXX_INTERNAL_QUERY_FIELDS_BUILDER_H
#define ORMXX_INTERNAL_QUERY_FIELDS_BUILDER_H

#include <string>

#include "fmt/core.h"

#include "../interface/sql_statement.h"
#include "../options/field_type.h"
#include "./field_to_sql_statement_field_value.h"

namespace ormxx {

namespace internal {

class InjectUtility;
class SQLUtility;

template <typename T>
class QueryFieldsBuilder {
    using Self = QueryFieldsBuilder<T>;

    friend class ::ormxx::internal::InjectUtility;
    friend class ::ormxx::internal::SQLUtility;

public:
    QueryFieldsBuilder() = default;

public:
    Self Eq(const T& t) {
        Self s = *this;

        auto f = SQLStatement::Field{};
        f.field_type = field_type;
        f.value = internal::FieldToSQLStatementFieldValue(&t);

        s.sql_statement_.AppendSQLString(fmt::format("(`{}` = ?)", field_name));
        s.sql_statement_.AppendField(f);

        return s;
    }

    Self Eq(T&& t) {
        auto _t = std::move(t);
        return Eq(_t);
    }

    Self Neq(const T& t) {
        Self s = *this;

        auto f = SQLStatement::Field{};
        f.field_type = field_type;
        f.value = internal::FieldToSQLStatementFieldValue(&t);

        s.sql_statement_.AppendSQLString(fmt::format("(`{}` <> ?)", field_name));
        s.sql_statement_.AppendField(f);

        return s;
    }

    Self Neq(T&& t) {
        auto _t = std::move(t);
        return New(_t);
    }

    Self Gt(const T& t) {
        Self s = *this;

        auto f = SQLStatement::Field{};
        f.field_type = field_type;
        f.value = internal::FieldToSQLStatementFieldValue(&t);

        s.sql_statement_.AppendSQLString(fmt::format("(`{}` > ?)", field_name));
        s.sql_statement_.AppendField(f);

        return s;
    }

    Self Gt(T&& t) {
        auto _t = std::move(t);
        return Gt(_t);
    }

    Self Gte(const T& t) {
        Self s = *this;

        auto f = SQLStatement::Field{};
        f.field_type = field_type;
        f.value = internal::FieldToSQLStatementFieldValue(&t);

        s.sql_statement_.AppendSQLString(fmt::format("(`{}` >= ?)", field_name));
        s.sql_statement_.AppendField(f);

        return s;
    }

    Self Gte(T&& t) {
        auto _t = std::move(t);
        return Gte(_t);
    }

    Self Lt(const T& t) {
        Self s = *this;

        auto f = SQLStatement::Field{};
        f.field_type = field_type;
        f.value = internal::FieldToSQLStatementFieldValue(&t);

        s.sql_statement_.AppendSQLString(fmt::format("(`{}` < ?)", field_name));
        s.sql_statement_.AppendField(f);

        return s;
    }

    Self Lt(T&& t) {
        auto _t = std::move(t);
        return Lt(_t);
    }

    Self Lte(const T& t) {
        Self s = *this;

        auto f = SQLStatement::Field{};
        f.field_type = field_type;
        f.value = internal::FieldToSQLStatementFieldValue(&t);

        s.sql_statement_.AppendSQLString(fmt::format("(`{}` <= ?)", field_name));
        s.sql_statement_.AppendField(f);

        return s;
    }

    Self Lte(T&& t) {
        auto _t = std::move(t);
        return Lte(_t);
    }

    Self Like(const T& t) {
        Self s = *this;

        auto f = SQLStatement::Field{};
        f.field_type = field_type;
        f.value = internal::FieldToSQLStatementFieldValue(&t);

        s.sql_statement_.AppendSQLString(fmt::format("(`{}` LIKE ?)", field_name));
        s.sql_statement_.AppendField(f);

        return s;
    }

    Self Like(T&& t) {
        auto _t = std::move(t);
        return Like(_t);
    }

    Self Between(const T& l, const T& r) {
        Self s = *this;

        auto l_field = SQLStatement::Field{};
        l_field.field_type = field_type;
        l_field.value = internal::FieldToSQLStatementFieldValue(&l);

        auto r_field = SQLStatement::Field{};
        r_field.field_type = field_type;
        r_field.value = internal::FieldToSQLStatementFieldValue(&r);

        s.sql_statement_.AppendSQLString(fmt::format("(`{}` BETWEEN ? AND ?)", field_name));
        s.sql_statement_.AppendField(l_field);
        s.sql_statement_.AppendField(r_field);

        return s;
    }

    Self Between(T&& l, T&& r) {
        auto _l = std::move(l);
        auto _r = std::move(r);
        return Between(_l, _r);
    }

    Self NotBetween(const T& l, const T& r) {
        Self s = *this;

        auto l_field = SQLStatement::Field{};
        l_field.field_type = field_type;
        l_field.value = internal::FieldToSQLStatementFieldValue(&l);

        auto r_field = SQLStatement::Field{};
        r_field.field_type = field_type;
        r_field.value = internal::FieldToSQLStatementFieldValue(&r);

        s.sql_statement_.AppendSQLString(fmt::format("(`{}` NOT BETWEEN ? AND ?)", field_name));
        s.sql_statement_.AppendField(l_field);
        s.sql_statement_.AppendField(r_field);

        return s;
    }

    Self NotBetween(T&& l, T&& r) {
        auto _l = std::move(l);
        auto _r = std::move(r);
        return NotBetween(_l, _r);
    }

    Self Asc() {
        Self s = *this;
        s.sql_statement_.AppendSQLString(fmt::format("`{}` ASC", field_name));

        return s;
    }

    Self Desc() {
        Self s = *this;
        s.sql_statement_.AppendSQLString(fmt::format("`{}` DESC", field_name));

        return s;
    }

private:
    void init() {
        default_sql_statement_.SetSQLString(fmt::format("`{}`", field_name));
    }

    const SQLStatement& getSQLStatement() const {
        if (!sql_statement_.Empty()) {
            return sql_statement_;
        }

        return default_sql_statement_;
    }

private:
    std::string origin_field_name{""};
    std::string field_name{""};
    FieldTypeStruct field_type{};

private:
    SQLStatement sql_statement_{};
    SQLStatement default_sql_statement_{};
};

}  // namespace internal
}  // namespace ormxx

#endif  // ORMXX_INTERNAL_QUERY_FIELDS_BUILDER_H
