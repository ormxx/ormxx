#ifndef ORMXX_INTERNAL_MACROS_H
#define ORMXX_INTERNAL_MACROS_H

#include <functional>
#include <string>

#include "../options/table_options.h"
#include "../types_check/has_ormxx_external_get_table_options.h"
#include "../types_check/has_ormxx_external_struct_schema_entrance.h"
#include "../types_check/has_ormxx_get_table_options.h"
#include "../types_check/has_ormxx_struct_schema_entrance.h"
#include "./create_entrance_field_options.h"
#include "./inject_entrance.h"
#include "./utils.h"

#define ORMXX_STR(x) #x

#define ORMXX_STRUCT_SCHEMA_DECLARE_BEGIN(Struct, ...)                                                     \
private:                                                                                                   \
    friend class ::ormxx::has_ormxx_get_table_options<Struct>;                                             \
    friend class ::ormxx::has_ormxx_get_table_options<const Struct>;                                       \
    friend class ::ormxx::has_ormxx_struct_schema_entrance<Struct>;                                        \
    friend class ::ormxx::has_ormxx_struct_schema_entrance<const Struct>;                                  \
    friend class ::ormxx::internal::InjectEntrance;                                                        \
                                                                                                           \
    static ::ormxx::TableOptions __ORMXX_GetTableOptions() {                                               \
        static const auto options = std::invoke([]() {                                                     \
            ::ormxx::TableOptions options;                                                                 \
            options.origin_struct_name = ::ormxx::internal::Utils::GetOriginStructName(ORMXX_STR(Struct)); \
            options.table_name = ::ormxx::internal::Utils::GetOriginStructName(ORMXX_STR(Struct));         \
                                                                                                           \
            ::ormxx::TableOptions::ApplyTableOptions(options, ##__VA_ARGS__);                              \
            return options;                                                                                \
        });                                                                                                \
                                                                                                           \
        return options;                                                                                    \
    }                                                                                                      \
                                                                                                           \
    template <typename T, std::enable_if_t<std::is_same_v<Struct, std::remove_const_t<T>>, bool> = true,   \
            typename Func>                                                                                 \
    static void __ORMXX_StructSchemaEntrance(T* s, Func&& func) {                                          \
        using _Struct = Struct;

#define ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(field, ...)                              \
    {                                                                              \
        auto options = ::ormxx::internal::CreateEntranceFieldOptions(              \
                s, &(s->field), &_Struct::field, ORMXX_STR(field), ##__VA_ARGS__); \
        func(&(s->field), options);                                                \
    }

#define ORMXX_STRUCT_SCHEMA_DECLARE_END }

#define ORMXX_EXTERNAL_STRUCT_SCHEMA_DECLARE_BEGIN(Struct, ...)                                            \
    template <typename T, std::enable_if_t<std::is_same_v<Struct, std::remove_const_t<T>>, bool> = true>   \
    static ::ormxx::TableOptions __ORMXXExternal_GetTableOptions([[maybe_unused]] T* s) {                  \
        static const auto options = std::invoke([]() {                                                     \
            ::ormxx::TableOptions options;                                                                 \
            options.origin_struct_name = ::ormxx::internal::Utils::GetOriginStructName(ORMXX_STR(Struct)); \
            options.table_name = ::ormxx::internal::Utils::GetOriginStructName(ORMXX_STR(Struct));         \
                                                                                                           \
            ::ormxx::TableOptions::ApplyTableOptions(options, ##__VA_ARGS__);                              \
            return options;                                                                                \
        });                                                                                                \
                                                                                                           \
        return options;                                                                                    \
    }                                                                                                      \
                                                                                                           \
    template <typename T, std::enable_if_t<std::is_same_v<Struct, std::remove_const_t<T>>, bool> = true,   \
            typename Func>                                                                                 \
    static auto __ORMXXExternal_StructSchemaEntrance(T* s, Func&& func) {                                  \
        using _Struct = Struct;

#define ORMXX_EXTERNAL_STRUCT_SCHEMA_DECLARE_FIELD(field, ...) ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(field, ##__VA_ARGS__)

#define ORMXX_EXTERNAL_STRUCT_SCHEMA_DECLARE_END }

#endif  // ORMXX_INTERNAL_MACROS_H
