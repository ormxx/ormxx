#ifndef ORMXX_SQL_GENERATE_SELECT_SQL_STATEMENT_H
#define ORMXX_SQL_GENERATE_SELECT_SQL_STATEMENT_H

#include <cstddef>
#include <string>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../interface/sql_statement.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../internal/query_builder_sql_data.h"
#include "../types_check/has_ormxx_inject.h"
#include "./sql_utility.h"

namespace ormxx {

inline ResultOr<SQLStatement> GenerateSelectSQLStatement(const internal::QueryBuilderSQLData& sql_data) {
    SQLStatement sql_statement{};

    sql_statement.AppendSQLString(
            fmt::format("SELECT {} FROM {}", sql_data.sql_select.GetSQLString(), sql_data.sql_from.GetSQLString()));
    sql_statement.AppendFields(sql_data.sql_select.GetFields());
    sql_statement.AppendFields(sql_data.sql_from.GetFields());

    if (!sql_data.sql_where.Empty()) {
        sql_statement.AppendSQLString(fmt::format(" WHERE {}", sql_data.sql_where.GetSQLString()));
        sql_statement.AppendFields(sql_data.sql_where.GetFields());
    }

    if (!sql_data.sql_order.Empty()) {
        sql_statement.AppendSQLString(fmt::format(" ORDER BY {}", sql_data.sql_order.GetSQLString()));
        sql_statement.AppendFields(sql_data.sql_order.GetFields());
    }

    if (!sql_data.sql_limit.Empty()) {
        sql_statement.AppendSQLString(fmt::format(" LIMIT {}", sql_data.sql_limit.GetSQLString()));
        sql_statement.AppendFields(sql_data.sql_limit.GetFields());
    }

    if (!sql_data.sql_offset.Empty()) {
        sql_statement.AppendSQLString(fmt::format(" OFFSET {}", sql_data.sql_offset.GetSQLString()));
        sql_statement.AppendFields(sql_data.sql_offset.GetFields());
    }

    sql_statement.AppendSQLString(";");

    return sql_statement;
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_SELECT_SQL_STATEMENT_H
