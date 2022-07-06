#ifndef ORMXX_TYPES_CHECK_HAS_ORMXX_INJECT_H
#define ORMXX_TYPES_CHECK_HAS_ORMXX_INJECT_H

#include "./has_ormxx_get_table_options.h"
#include "./has_ormxx_struct_schema_entrance.h"

namespace ormxx::internal {

template <typename T>
inline constexpr bool has_ormxx_inject_v = has_ormxx_struct_schema_entrance_v<T>&& has_ormxx_get_table_options_v<T>;

}  // namespace ormxx::internal

#endif  // ORMXX_TYPES_CHECK_HAS_ORMXX_INJECT_H
