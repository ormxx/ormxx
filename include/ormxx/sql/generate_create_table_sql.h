#ifndef ORMXX_SQL_GENERATE_CREATE_TABLE_SQL_H
#define ORMXX_SQL_GENERATE_CREATE_TABLE_SQL_H

#include "../internal/inject_entrance.h"

namespace ormxx {

template <typename T>
std::string GenerateCreateTableSQL([[maybe_unused]] const T& t) {}

};  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_CREATE_TABLE_SQL_H
