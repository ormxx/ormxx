#ifndef ORMXX_INTERNAL_FIELD_TO_STRING_H
#define ORMXX_INTERNAL_FIELD_TO_STRING_H

#include <string>
#include <type_traits>

#include "fmt/core.h"

#include "../types_check/has_std_to_string.h"

namespace ormxx::internal {

template <typename T, std::enable_if_t<has_std_to_string_v<T>, bool> = true>
inline std::string FieldToString(T* t) {
    return std::to_string(*t);
}

inline std::string FieldToString(bool* t) {
    return *t ? "1" : "0";
}

inline std::string FieldToString(std::string* s) {
    return fmt::format("'{}'", *s);
}

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_FIELD_TO_STRING_H
