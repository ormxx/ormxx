#ifndef ORMXX_TYPES_CHECK_IS_FIELD_BUILDER_H
#define ORMXX_TYPES_CHECK_IS_FIELD_BUILDER_H

#include "../internal/field_builder.h"
#include "./is_specialization.h"

namespace ormxx::internal {

template <typename... T>
inline constexpr bool is_field_builder_v = (is_specialization<T, internal::FieldBuilder>::value && ...);

}  // namespace ormxx::internal

#endif  // ORMXX_TYPES_CHECK_IS_FIELD_BUILDER_H
