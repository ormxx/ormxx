#ifndef ORMXX_INTERNAL_FIELD_OPTIONS_H
#define ORMXX_INTERNAL_FIELD_OPTIONS_H

#include <optional>
#include <string>
#include <string_view>

namespace ormxx {

namespace internal {

template <typename T, typename F>
struct FieldOptionsStruct {
    std::string origin_field_name{""};
    F struct_field_type;

    std::string field_name{""};
    std::string comment{""};
    bool required{false};
    std::optional<T> default_value{std::nullopt};
};

}  // namespace internal

class FieldOptions {
public:
    static auto WithFieldName(const std::string& field_name) {
        return [field_name](auto& options) {
            options.field_name = field_name;
        };
    }

    static auto WithComment(const std::string& comment) {
        return [comment](auto& options) {
            options.comment = comment;
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

    template <typename T, typename F, typename... Opt>
    static auto ApplyFieldOptions(internal::FieldOptionsStruct<T, F>& options, Opt&&... opts) {
        (std::forward<Opt>(opts)(options), ...);
        return options;
    }

    template <typename T, typename F, typename... Opt>
    static auto CreateFieldOptions(Opt&&... opts) {
        internal::FieldOptionsStruct<T, F> options;
        return ApplySchemaOptions(options, std::forward<Opt>(opts)...);
    }
};

}  // namespace ormxx

#endif  // ORMXX_INTERNAL_FIELD_OPTIONS_H
