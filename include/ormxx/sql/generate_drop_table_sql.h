#ifndef ORMXX_SQL_GENERATE_DROP_TABLE_SQL_H
#define ORMXX_SQL_GENERATE_DROP_TABLE_SQL_H

#include <string>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../internal/inject_entrance.h"

namespace ormxx {

template <typename T>
ResultOr<std::string> GenerateDropTableSQL() {
    const auto table_options = internal::InjectEntrance::GetTableOptions<T>(nullptr);
    return fmt::format("DROP TABLE IF EXISTS `{}`;", table_options.table_name);
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_DROP_TABLE_SQL_H
