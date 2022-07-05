#ifndef ORMXX_TYPES_CHECK_HAS_ORMXX_GET_TABLE_OPTIONS_H
#define ORMXX_TYPES_CHECK_HAS_ORMXX_GET_TABLE_OPTIONS_H

#include <type_traits>

#include "../options/table_options.h"

namespace ormxx {

template <typename T>
class has_ormxx_get_table_options {
private:
    template <typename U>
    static constexpr auto check(int) ->
            typename std::is_same<decltype(U::__ORMXX_GetTableOptions()), ::ormxx::TableOptions>::type;

    template <typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<T>(0)) type;

public:
    static constexpr bool value = type::value;
};

template <typename T>
inline constexpr bool has_ormxx_get_table_options_v = has_ormxx_get_table_options<T>::value;

}  // namespace ormxx

#endif  // ORMXX_TYPES_CHECK_HAS_ORMXX_GET_TABLE_OPTIONS_H
