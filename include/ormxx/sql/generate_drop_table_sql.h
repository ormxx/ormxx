#ifndef ORMXX_SQL_GENERATE_DROP_TABLE_SQL_H
#define ORMXX_SQL_GENERATE_DROP_TABLE_SQL_H

#include <string>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../internal/inject_entrance.h"
#include "../types_check/has_ormxx_inject.h"

namespace ormxx {

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<std::string> GenerateDropTableSQL() {
    const auto table_options = internal::InjectEntrance::GetTableOptions<T>(nullptr);
    return fmt::format("DROP TABLE IF EXISTS `{}`;", table_options.table_name);
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_DROP_TABLE_SQL_H
