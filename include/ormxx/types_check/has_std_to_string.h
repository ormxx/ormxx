#ifndef ORMXX_TYPES_CHECK_HAS_STD_TO_STRING_H
#define ORMXX_TYPES_CHECK_HAS_STD_TO_STRING_H

#include <string>
#include <type_traits>

namespace ormxx::internal {

template <typename T>
class has_std_to_string {
private:
    template <typename U>
    static auto check(int) -> decltype(std::to_string(std::declval<U>()), std::true_type());

    template <typename U>
    static std::false_type check(...);

public:
    enum { value = std::is_same<decltype(check<T>(0)), std::true_type>::value };
};

template <typename T>
inline constexpr bool has_std_to_string_v = has_std_to_string<T>::value;

}  // namespace ormxx::internal

#endif  // ORMXX_TYPES_CHECK_HAS_STD_TO_STRING_H
