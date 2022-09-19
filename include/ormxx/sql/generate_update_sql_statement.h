#ifndef ORMXX_SQL_GENERATE_UPDATE_SQL_STATEMENT_H
#define ORMXX_SQL_GENERATE_UPDATE_SQL_STATEMENT_H

#include "../interface/result.h"
#include "../interface/sql_statement.h"
#include "../internal/field_to_sql_statement_field_value.h"
#include "../internal/inject_utility.h"
#include "../types_check/has_ormxx_inject.h"
#include "../types_check/is_field_builder.h"
#include "../types_check/is_specialization.h"
#include "./sql_expr.h"
#include "./sql_utility.h"

namespace ormxx {

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
ResultOr<SQLStatement> GenerateUpdateSQLStatement(T* t) {
    RESULT_VALUE_OR_RETURN(const auto primary_key_field_name, internal::InjectUtility::GetPrimaryKeyFieldName<T>());

    const auto table_options = internal::InjectEntrance::GetTableOptions(t);

    SQLStatement sql_statement{};

    sql_statement.AppendSQLString(fmt::format("UPDATE `{}` SET ", table_options.table_name));

    RESULT_VALUE_OR_RETURN(const auto set_sql_statement, internal::SQLUtility::GenerateUpdateSetSQLStatement(*t));
    sql_statement.Append(set_sql_statement);

    sql_statement.AppendSQLString(" WHERE ");

    {
        const auto options = internal::StructSchemaEntranceOptionsBuilder()
                                     .WithVisitField()
                                     .WithVisitFieldByName(primary_key_field_name)
                                     .Build();
        internal::InjectEntrance::StructSchemaEntrance(t, options, [&sql_statement](auto&& field, auto&& options) {
            sql_statement.AppendSQLString(fmt::format("`{}` = ?", options.field_name));

            auto f = SQLStatement::Field{};
            f.field_type = options.field_type;
            f.value = internal::FieldToSQLStatementFieldValue(field);

            sql_statement.AppendField(f);
        });
    }

    sql_statement.AppendSQLString(";");

    return sql_statement;
}

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
ResultOr<SQLStatement> GenerateUpdateSQLStatement(const internal::SQLExpr& sql_expr, const T& t) {
    SQLStatement s{};

    const auto table_options = internal::InjectEntrance::GetTableOptions(&t);

    s.AppendSQLString(fmt::format("UPDATE `{}` SET ", table_options.table_name));

    RESULT_VALUE_OR_RETURN(const auto update_sql_statement, internal::SQLUtility::GenerateUpdateSetSQLStatement(t));
    s.Append(update_sql_statement);

    if (!sql_expr.sql_where.Empty()) {
        s.AppendSQLString(fmt::format(" WHERE {}", sql_expr.sql_where.GetSQLString()));
        s.AppendFields(sql_expr.sql_where.GetFields());
    }

    if (!sql_expr.sql_order.Empty()) {
        s.AppendSQLString(fmt::format(" ORDER BY {}", sql_expr.sql_order.GetSQLString()));
        s.AppendFields(sql_expr.sql_order.GetFields());
    }

    if (!sql_expr.sql_limit.Empty()) {
        s.AppendSQLString(fmt::format(" LIMIT {}", sql_expr.sql_limit.GetSQLString()));
        s.AppendFields(sql_expr.sql_limit.GetFields());
    }

    s.AppendSQLString(";");

    return s;
}

template <typename T,
          std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true,
          typename... FieldBuilder,
          std::enable_if_t<internal::is_field_builder_v<FieldBuilder...>, bool> = true>
ResultOr<SQLStatement> GenerateUpdateSQLStatement(const internal::SQLExpr& sql_expr, FieldBuilder&&... field_builder) {
    SQLStatement s{};
    T t{};

    const auto table_options = internal::InjectEntrance::GetTableOptions(&t);

    s.AppendSQLString(fmt::format("UPDATE `{}` SET ", table_options.table_name));

    RESULT_VALUE_OR_RETURN(
            const auto update_sql_statement,
            internal::SQLUtility::GenerateUpdateSetSQLStatement(std::forward<FieldBuilder>(field_builder)...));
    s.Append(update_sql_statement);

    if (!sql_expr.sql_where.Empty()) {
        s.AppendSQLString(fmt::format(" WHERE {}", sql_expr.sql_where.GetSQLString()));
        s.AppendFields(sql_expr.sql_where.GetFields());
    }

    if (!sql_expr.sql_order.Empty()) {
        s.AppendSQLString(fmt::format(" ORDER BY {}", sql_expr.sql_order.GetSQLString()));
        s.AppendFields(sql_expr.sql_order.GetFields());
    }

    if (!sql_expr.sql_limit.Empty()) {
        s.AppendSQLString(fmt::format(" LIMIT {}", sql_expr.sql_limit.GetSQLString()));
        s.AppendFields(sql_expr.sql_limit.GetFields());
    }

    s.AppendSQLString(";");

    return s;
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_UPDATE_SQL_STATEMENT_H
