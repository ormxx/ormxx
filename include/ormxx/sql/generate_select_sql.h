#ifndef ORMXX_SQL_GENERATE_SELECT_SQL_H
#define ORMXX_SQL_GENERATE_SELECT_SQL_H

#include <cstddef>
#include <string>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../types_check/has_ormxx_inject.h"
#include "./sql_utility.h"

namespace ormxx {

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<std::string> GenerateSelectSQL(T* t) {
    const auto table_options = internal::InjectEntrance::GetTableOptions(t);
    const auto select_sql = internal::SQLUtility::GenerateSelectSQLString(t);

    std::string sql = fmt::format("{} FROM `{}` LIMIT 1;", select_sql, table_options.table_name);

    return sql;
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_SELECT_SQL_H
