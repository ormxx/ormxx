#ifndef ORMXX_SQL_GENERATE_INSERT_H
#define ORMXX_SQL_GENERATE_INSERT_H

#include <string>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../internal/inject_entrance.h"

namespace ormxx {

template <typename T>
ResultOr<std::string> GenerateInsertSQL(T* t) {
    const auto table_options = internal::InjectEntrance::GetTableOptions(t);
    std::string sql = "";
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_INSERT_H
