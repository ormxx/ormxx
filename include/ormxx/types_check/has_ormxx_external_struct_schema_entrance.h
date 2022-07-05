#ifndef ORMXX_TYPES_CHECK_HAS_ORMXX_EXTERNAL_STRUCT_SCHEMA_ENTRANCE_H
#define ORMXX_TYPES_CHECK_HAS_ORMXX_EXTERNAL_STRUCT_SCHEMA_ENTRANCE_H

#include <type_traits>

namespace ormxx::internal {

template <typename T>
class has_ormxx_external_struct_schema_entrance {
private:
    template <typename U>
    static constexpr auto check(int)
            -> decltype(__ORMXX_StructSchemaEntrance(std::declval<U*>(), nullptr), std::true_type());

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T>
inline constexpr bool has_ormxx_external_struct_schema_entrance_v = has_ormxx_external_struct_schema_entrance<T>::value;

}  // namespace ormxx::internal

#endif  // ORMXX_TYPES_CHECK_HAS_ORMXX_EXTERNAL_STRUCT_SCHEMA_ENTRANCE_H
