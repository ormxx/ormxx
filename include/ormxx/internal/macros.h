#ifndef ORMXX_INTERNAL_MACROS_H
#define ORMXX_INTERNAL_MACROS_H

#include <functional>
#include <string>

#include "../options/table_options.h"
#include "../types_check/has_ormxx_external_struct_schema_entrance.h"
#include "../types_check/has_ormxx_struct_schema_entrance.h"
#include "./create_entrance_field_options.h"

namespace internal {

std::string GetOriginStructName(const std::string& origin_struct_name) {
    std::string res = "";

    for (size_t i = origin_struct_name.size() - 1; i >= 0; i--) {
        if (origin_struct_name[i] == ':') {
            break;
        }

        res += origin_struct_name[i];
    }

    return res;
}

}  // namespace internal

#define ORMXX_STR(x) #x

#define ORMXX_STRUCT_SCHEMA_DECLARE_BEGIN(Struct, ...)                                                   \
private:                                                                                                 \
    friend class ::ormxx::has_ormxx_struct_schema_entrance<Struct>;                                      \
    friend class ::ormxx::has_ormxx_struct_schema_entrance<const Struct>;                                \
    friend class ::ormxx::internal::StructInjectEntranceClass;                                           \
                                                                                                         \
    static ::ormxx::TableOptions __ORMXX_GetTableOptions() {                                             \
        static const auto options = std::invoke([]() {                                                   \
            ::ormxx::TableOptions options;                                                               \
            options.origin_struct_name = GetOriginStructName(ORMXX_STR(Struct));                         \
                                                                                                         \
            ::ormxx::TableOptions::ApplyTableOptions(options, __VA_ARGS__);                              \
        });                                                                                              \
                                                                                                         \
        return options;                                                                                  \
    }                                                                                                    \
                                                                                                         \
    template <typename T, std::enable_if_t<std::is_same_v<Struct, std::remove_const_t<T>>, bool> = true, \
            typename Func>                                                                               \
    static void __ORMXX_StructSchemaEntrance(T* s, Func&& func) {                                        \
        using _Struct = Struct;

#define ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(field, ...)                             \
    {                                                                             \
        auto options = ::ormxx::internal::CreateEntranceSchemaOptions(            \
                s, &(s->field), _Struct::field, ORMXX_STR(field), ##__VA_ARGS__); \
        func(&(s->field), options);                                               \
    }

#define ORMXX_STRUCT_SCHEMA_DECLARE_END }

#define ORMXX_EXTERNAL_STRUCT_SCHEMA_DECLARE_BEGIN(Struct)                                               \
    static ::ormxx::TableOptions __ORMXXExternal_GetTableOptions() {                                     \
        static const auto options = std::invoke([]() {                                                   \
            ::ormxx::TableOptions options;                                                               \
            options.origin_struct_name = GetOriginStructName(ORMXX_STR(Struct));                         \
                                                                                                         \
            ::ormxx::TableOptions::ApplyTableOptions(options, __VA_ARGS__);                              \
        });                                                                                              \
                                                                                                         \
        return options;                                                                                  \
    }                                                                                                    \
                                                                                                         \
    template <typename T, std::enable_if_t<std::is_same_v<Struct, std::remove_const_t<T>>, bool> = true, \
            typename Func>                                                                               \
    static auto __ORMXXExternal_StructSchemaEntrance(T* s, Func&& func) {                                \
        using _Struct = Struct;

#define ORMXX_EXTERNAL_STRUCT_SCHEMA_DECLARE_FIELD(field, ...) ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(field, ##__VA_ARGS__)

#define ORMXX_EXTERNAL_STRUCT_SCHEMA_DECLARE_END }

#endif  // ORMXX_INTERNAL_MACROS_H
