#ifndef ORMXX_TYPES_CHECK_IS_SPECIALIZATION_H
#define ORMXX_TYPES_CHECK_IS_SPECIALIZATION_H

#include <type_traits>

namespace ormxx::internal {

template <typename Test, template <typename...> class Ref>
struct is_specialization : std::false_type {};

template <template <typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

}  // namespace ormxx::internal

#endif  // ORMXX_TYPES_CHECK_IS_SPECIALIZATION_H
