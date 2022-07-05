#ifndef ORMXX_TYPES_CHECK_IS_VISIT_KEY_FUNC_H
#define ORMXX_TYPES_CHECK_IS_VISIT_KEY_FUNC_H

#include "../options/key_options.h"

namespace ormxx::internal {

template <typename T>
class is_visit_key_func {
private:
    template <typename U>
    static auto check(int) -> decltype(std::declval<U>()(std::declval<KeyOptions>()), std::true_type());

    template <typename U>
    static std::false_type check(...);

public:
    enum { value = std::is_same<decltype(check<T>(0)), std::true_type>::value };
};

template <typename T>
inline constexpr bool is_visit_key_func_v = is_visit_key_func<T>::value;

}  // namespace ormxx::internal

#endif  // ORMXX_TYPES_CHECK_IS_VISIT_KEY_FUNC_H
