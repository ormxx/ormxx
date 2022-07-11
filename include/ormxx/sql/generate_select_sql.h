#ifndef ORMXX_SQL_GENERATE_SELECT_SQL_H
#define ORMXX_SQL_GENERATE_SELECT_SQL_H

#include <cstddef>
#include <string>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../internal/query_builder_sql_data.h"
#include "../types_check/has_ormxx_inject.h"
#include "./sql_utility.h"

namespace ormxx {

inline ResultOr<std::string> GenerateSelectSQL(internal::QueryBuilderSQLData& sql_data) {
    std::string sql = "";

    sql += fmt::format("SELECT {} FROM {}", sql_data.sql_select, sql_data.sql_from);

    if (!sql_data.sql_where.empty()) {
        sql += fmt::format(" WHERE {}", sql_data.sql_where);
    }

    if (!sql_data.sql_limit.empty()) {
        sql += fmt::format(" LIMIT {}", sql_data.sql_limit);
    }

    if (!sql_data.sql_offset.empty()) {
        sql += fmt::format(" OFFSET {}", sql_data.sql_offset);
    }

    sql += ";";

    return sql;
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_SELECT_SQL_H
