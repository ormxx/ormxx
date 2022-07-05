#ifndef ORMXX_TYPES_CHECK_IS_VISIT_FIELD_FUNC_H
#define ORMXX_TYPES_CHECK_IS_VISIT_FIELD_FUNC_H

#include "./is_visit_key_func.h"

namespace ormxx::internal {

template <typename T>
inline constexpr bool is_visit_field_func_v = !is_visit_key_func_v<T>;

}  // namespace ormxx::internal

#endif  // ORMXX_TYPES_CHECK_IS_VISIT_FIELD_FUNC_H
