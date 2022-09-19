#ifndef ORMXX_SQL_GENERATE_SELECT_SQL_STATEMENT_H
#define ORMXX_SQL_GENERATE_SELECT_SQL_STATEMENT_H

#include <cstddef>
#include <string>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../interface/sql_statement.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../types_check/has_ormxx_inject.h"
#include "./sql_expr.h"
#include "./sql_utility.h"

namespace ormxx {

inline ResultOr<SQLStatement> GenerateSelectSQLStatement(const internal::SQLExpr& sql_expr) {
    SQLStatement sql_statement{};

    sql_statement.AppendSQLString(
            fmt::format("SELECT {} FROM {}", sql_expr.sql_select.GetSQLString(), sql_expr.sql_from.GetSQLString()));
    sql_statement.AppendFields(sql_expr.sql_select.GetFields());
    sql_statement.AppendFields(sql_expr.sql_from.GetFields());

    if (!sql_expr.sql_where.Empty()) {
        sql_statement.AppendSQLString(fmt::format(" WHERE {}", sql_expr.sql_where.GetSQLString()));
        sql_statement.AppendFields(sql_expr.sql_where.GetFields());
    }

    if (!sql_expr.sql_order.Empty()) {
        sql_statement.AppendSQLString(fmt::format(" ORDER BY {}", sql_expr.sql_order.GetSQLString()));
        sql_statement.AppendFields(sql_expr.sql_order.GetFields());
    }

    if (!sql_expr.sql_limit.Empty()) {
        sql_statement.AppendSQLString(fmt::format(" LIMIT {}", sql_expr.sql_limit.GetSQLString()));
        sql_statement.AppendFields(sql_expr.sql_limit.GetFields());
    }

    if (!sql_expr.sql_offset.Empty()) {
        sql_statement.AppendSQLString(fmt::format(" OFFSET {}", sql_expr.sql_offset.GetSQLString()));
        sql_statement.AppendFields(sql_expr.sql_offset.GetFields());
    }

    sql_statement.AppendSQLString(";");

    return sql_statement;
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_SELECT_SQL_STATEMENT_H
