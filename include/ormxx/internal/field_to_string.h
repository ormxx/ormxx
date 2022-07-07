#ifndef ORMXX_INTERNAL_FIELD_TO_STRING_H
#define ORMXX_INTERNAL_FIELD_TO_STRING_H

#include <optional>
#include <string>
#include <type_traits>

#include "fmt/core.h"

#include "../types_check/has_std_to_string.h"

namespace ormxx::internal {

template <typename T, std::enable_if_t<has_std_to_string_v<std::remove_cv_t<T>>, bool> = true>
inline std::string FieldToString(T* t) {
    return std::to_string(*t);
}

template <typename T, std::enable_if_t<std::is_same_v<bool, std::remove_cv_t<T>>, bool> = true>
inline std::string FieldToString(const T* t) {
    return *t ? "1" : "0";
}

template <typename T, std::enable_if_t<std::is_same_v<std::string, std::remove_cv_t<T>>, bool> = true>
inline std::string FieldToString(const T* s) {
    return fmt::format("'{}'", *s);
}

template <typename T,
          std::enable_if_t<has_std_to_string_v<std::remove_cv_t<T>> || std::is_same_v<bool, std::remove_cv_t<T>> ||
                                   std::is_same_v<std::string, std::remove_cv_t<T>>,
                           bool> = true>
inline std::string FieldToString(const std::optional<T>* t) {
    if (!t->has_value()) {
        return "NULL";
    }

    return FieldToString(&t->value());
}

template <typename T,
          std::enable_if_t<has_std_to_string_v<std::remove_cv_t<T>> || std::is_same_v<bool, std::remove_cv_t<T>> ||
                                   std::is_same_v<std::string, std::remove_cv_t<T>>,
                           bool> = true>
inline std::string FieldToString(std::optional<T>* t) {
    return FieldToString(static_cast<const std::optional<T>*>(t));
}

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_FIELD_TO_STRING_H
