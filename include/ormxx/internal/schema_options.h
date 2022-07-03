#ifndef ORMXX_INTERNAL_SCHEMA_OPTIONS_H
#define ORMXX_INTERNAL_SCHEMA_OPTIONS_H

#include <optional>
#include <string>
#include <string_view>

namespace ormxx {

namespace internal {

template <typename T>
struct SchemaOptionsStruct {
    std::string field_name{""};
    bool required{false};
    std::optional<T> default_value{std::nullopt};
};

}  // namespace internal

class SchemaOptions {
public:
    static auto WithFieldName(const std::string& field_name) {
        return [field_name](auto& options) {
            options.field_name = field_name;
        };
    }

    static auto WithRequired(bool required) {
        return [required](auto& options) {
            options.required = required;
        };
    }

    template <typename T>
    static auto WithDefaultValue(T&& default_value) {
        return [default_value = std::forward<T>(default_value)](auto& options) {
            options.default_value = default_value;
        };
    }

    template <typename T, typename... Opt>
    static auto ApplySchemaOptions(internal::SchemaOptionsStruct<T>& options, Opt&&... opts) {
        (std::forward<Opt>(opts)(options), ...);
        return options;
    }

    template <typename T, typename... Opt>
    static auto CreateSchemaOptions(Opt&&... opts) {
        internal::SchemaOptionsStruct<T> options;
        return ApplySchemaOptions(options, std::forward<Opt>(opts)...);
    }
};

}  // namespace ormxx

#endif  // ORMXX_INTERNAL_SCHEMA_OPTIONS_H
