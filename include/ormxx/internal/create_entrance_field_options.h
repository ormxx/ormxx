#ifndef ORMXX_INTERNAL_CREATE_ENTRANCE_SCHEMA_OPTIONS_H
#define ORMXX_INTERNAL_CREATE_ENTRANCE_SCHEMA_OPTIONS_H

#include <string_view>
#include <type_traits>
#include <utility>

#include "../options/field_options.h"

namespace ormxx::internal {

class CreateEntranceFieldOptionsClass {
public:
    template <typename T, typename F, typename... Opt>
    auto operator()([[maybe_unused]] T* t, F struct_field_type, std::string_view field_name, Opt&&... opts) const {
        auto options = FieldOptionsStruct<std::remove_const_t<T>, F>{};
        options.origin_field_name = field_name;
        options.field_name = field_name;
        options.struct_field_type = struct_field_type;

        FieldOptions::ApplyFieldOptions(options, std::forward<Opt>(opts)...);
        return options;
    }

    template <typename T, typename F, typename... Opt>
    auto operator()([[maybe_unused]] std::optional<T>* t, F struct_field_type, std::string_view field_name,
            Opt&&... opts) const {
        auto options = FieldOptionsStruct<std::remove_const_t<T>, F>{};
        options.origin_field_name = field_name;
        options.field_name = field_name;
        options.struct_field_type = struct_field_type;

        FieldOptions::ApplyFieldOptions(options, std::forward<Opt>(opts)...);
        return options;
    }

    template <typename Struct, std::enable_if_t<std::is_const_v<Struct>, bool> = true, typename T, typename F,
            typename... Opt>
    auto operator()(
            [[maybe_unused]] Struct* s, T* t, F struct_field_type, std::string_view field_name, Opt&&... opts) const {
        return operator()(
                static_cast<const T*>(t), std::forward<F>(struct_field_type), field_name, std::forward<Opt>(opts)...);
    }

    template <typename Struct, std::enable_if_t<!std::is_const_v<Struct>, bool> = true, typename T, typename F,
            typename... Opt>
    auto operator()(
            [[maybe_unused]] Struct* s, T* t, F struct_field_type, std::string_view field_name, Opt&&... opts) const {
        return operator()(t, std::forward<F>(struct_field_type), field_name, std::forward<Opt>(opts)...);
    }
};

static const auto CreateEntranceFieldOptions = internal::CreateEntranceFieldOptionsClass();

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_CREATE_ENTRANCE_SCHEMA_OPTIONS_H
