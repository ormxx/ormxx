#ifndef ORMXX_SQL_GENERATE_DELETE_SQL_STATEMENT_H
#define ORMXX_SQL_GENERATE_DELETE_SQL_STATEMENT_H

#include <string>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../interface/sql_statement.h"
#include "../internal/field_to_string.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../types_check/has_ormxx_inject.h"
#include "./sql_expr.h"

namespace ormxx {

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<SQLStatement> GenerateDeleteSQLStatement(T* t) {
    RESULT_VALUE_OR_RETURN(const auto primary_key_field_name, internal::InjectUtility::GetPrimaryKeyFieldName<T>());
    const auto table_options = internal::InjectEntrance::GetTableOptions(t);

    SQLStatement sql_statement{};

    sql_statement.AppendSQLString(fmt::format("DELETE FROM `{}` WHERE ", table_options.table_name));

    {
        const auto options = internal::StructSchemaEntranceOptionsBuilder()
                                     .WithVisitField()
                                     .WithVisitFieldByName(primary_key_field_name)
                                     .Build();
        internal::InjectEntrance::StructSchemaEntrance(t, options, [&sql_statement](auto&& field, auto&& options) {
            sql_statement.AppendSQLString(fmt::format("`{}` = ?", options.field_name));

            auto f = SQLStatement::Field{
                    .field_type = options.field_type,
                    .value = internal::FieldToSQLStatementFieldValue(field),
            };

            sql_statement.AppendField(f);
        });
    }

    sql_statement.AppendSQLString(";");

    return sql_statement;
}

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<SQLStatement> GenerateDeleteSQLStatement(const internal::SQLExpr& sql_expr) {
    T t{};

    const auto table_options = internal::InjectEntrance::GetTableOptions(&t);

    SQLStatement s{};

    s.AppendSQLString(fmt::format("DELETE FROM `{}`", table_options.table_name));

    if (!sql_expr.sql_where.Empty()) {
        s.AppendSQLString(fmt::format(" WHERE {}", sql_expr.sql_where.GetSQLString()));
        s.AppendFields(sql_expr.sql_where.GetFields());
    }

    s.AppendSQLString(";");

    return s;
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_DELETE_SQL_STATEMENT_H
