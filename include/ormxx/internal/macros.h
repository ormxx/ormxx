#ifndef ORMXX_INTERNAL_MACROS_H
#define ORMXX_INTERNAL_MACROS_H

#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>

#include "../options/field_options.h"
#include "../options/key_options.h"
#include "../options/table_options.h"
#include "../types_check/has_ormxx_external_get_table_options.h"
#include "../types_check/has_ormxx_external_struct_schema_entrance.h"
#include "../types_check/has_ormxx_get_table_options.h"
#include "../types_check/has_ormxx_struct_schema_entrance.h"
#include "../types_check/is_visit_field_func.h"
#include "../types_check/is_visit_key_func.h"
#include "./column_builder.h"
#include "./create_entrance_field_options.h"
#include "./inject_entrance.h"
#include "./macros_utility.h"
#include "./struct_schema_entrance_options.h"
#include "./utils.h"

#define __ORMXX_STRUCT_SCHEMA_DECLARE_SET_AND_GET_FUNCTION(Field)       \
public:                                                                 \
    __ORMXX_Struct& Set##Field(decltype(__ORMXX_Struct::Field) value) { \
        __ORMXX_GetIsSetMap()[__ORMXX_STR(Field)] = true;               \
        this->Field = std::move(value);                                 \
        return *this;                                                   \
    }                                                                   \
                                                                        \
    const decltype(__ORMXX_Struct::Field)& Get##Field() const {         \
        return this->Field;                                             \
    }

#define __ORMXX_STRUCT_SCHEMA_DECLARE_COLUMN_BUILDER(Field)                                                   \
    ::ormxx::internal::ColumnBuilder<decltype(BaseStruct::Field)> Field{                                      \
            ::ormxx::internal::InjectUtility::GenerateColumnBuilder<BaseStruct, decltype(BaseStruct::Field)>( \
                    __ORMXX_STR(Field))};

#define ORMXX_STRUCT_SCHEMA_DECLARE_BEGIN(Struct, ...)                                          \
private:                                                                                        \
    friend class ::ormxx::internal::has_ormxx_get_table_options<Struct>;                        \
    friend class ::ormxx::internal::has_ormxx_get_table_options<const Struct>;                  \
    friend class ::ormxx::internal::has_ormxx_struct_schema_entrance<Struct>;                   \
    friend class ::ormxx::internal::has_ormxx_struct_schema_entrance<const Struct>;             \
    friend class ::ormxx::internal::InjectEntrance;                                             \
                                                                                                \
    using __ORMXX_Struct = Struct;                                                              \
    inline static const std::string __ORMXX_Struct_Name =                                       \
            ::ormxx::internal::Utils::GetOriginStructName(__ORMXX_STR(Struct));                 \
                                                                                                \
    std::unordered_map<std::string, bool> is_set_map;                                           \
                                                                                                \
    auto& __ORMXX_GetIsSetMap() {                                                               \
        return is_set_map;                                                                      \
    }                                                                                           \
                                                                                                \
    const auto& __ORMXX_GetIsSetMap() const {                                                   \
        return is_set_map;                                                                      \
    }                                                                                           \
                                                                                                \
    __ORMXX_EXPEND_FUNC_(__ORMXX_STRUCT_SCHEMA_DECLARE_SET_AND_GET_FUNCTION, __VA_ARGS__)       \
                                                                                                \
    class __ORMXX_ColumnBuilder {                                                               \
        using BaseStruct = Struct;                                                              \
                                                                                                \
    public:                                                                                     \
        __ORMXX_EXPEND_FUNC_(__ORMXX_STRUCT_SCHEMA_DECLARE_COLUMN_BUILDER, __VA_ARGS__)         \
    };                                                                                          \
                                                                                                \
    static const __ORMXX_ColumnBuilder& __ORMXX_NewColumnBuilder() {                            \
        static auto q = __ORMXX_ColumnBuilder{};                                                \
        return q;                                                                               \
    }                                                                                           \
                                                                                                \
    template <typename T,                                                                       \
              std::enable_if_t<std::is_same_v<Struct, std::remove_const_t<T>>, bool> = true,    \
              typename Func>                                                                    \
    static void __ORMXX_StructSchemaEntrance(                                                   \
            T* s, const ::ormxx::internal::StructSchemaEntranceOptions& options, Func&& func) { \
        using _Struct = Struct;                                                                 \
        size_t size = 0;

#define ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(field, ...)                                                    \
    if constexpr (::ormxx::internal::is_visit_field_func_v<Func>) {                                      \
        if (options.visit_field) {                                                                       \
            ++size;                                                                                      \
                                                                                                         \
            const std::string origin_field_name = std::string(__ORMXX_STR(field));                       \
            static const auto field_options = ::ormxx::internal::CreateEntranceFieldOptions(             \
                    s, &(s->field), &_Struct::field, origin_field_name, ##__VA_ARGS__);                  \
                                                                                                         \
            if (options.visit_for_each || (options.visit_field_by_index && options.index + 1 == size) || \
                (options.visit_field_by_name && origin_field_name == options.name) ||                    \
                (options.visit_field_by_is_set && s->is_set_map.count(origin_field_name) &&              \
                 s->is_set_map.at(origin_field_name))) {                                                 \
                func(&(s->field), field_options);                                                        \
            }                                                                                            \
        }                                                                                                \
    }

#define ORMXX_STRUCT_SCHEMA_DECLARE_KEY(__key_type, ...)                                                       \
    if constexpr (::ormxx::internal::is_visit_key_func_v<Func>) {                                              \
        if (options.visit_key) {                                                                               \
            ++size;                                                                                            \
                                                                                                               \
            static const auto key_options = std::invoke([]() {                                                 \
                return ::ormxx::KeyOptions::CreateKeyOptions(::ormxx::KeyOptions::WithKeyType(__key_type),     \
                                                             ##__VA_ARGS__);                                   \
            });                                                                                                \
                                                                                                               \
            if (options.visit_for_each || (options.visit_key_by_key_type && options.key_type == __key_type)) { \
                func(key_options);                                                                             \
            }                                                                                                  \
        }                                                                                                      \
    }

#define ORMXX_STRUCT_SCHEMA_DECLARE_END(...)                                  \
    }                                                                         \
                                                                              \
    static ::ormxx::TableOptions __ORMXX_GetTableOptions() {                  \
        static const auto options = std::invoke([]() {                        \
            ::ormxx::TableOptions options;                                    \
            options.origin_struct_name = __ORMXX_Struct_Name;                 \
            options.table_name = __ORMXX_Struct_Name;                         \
                                                                              \
            ::ormxx::TableOptions::ApplyTableOptions(options, ##__VA_ARGS__); \
            return options;                                                   \
        });                                                                   \
                                                                              \
        return options;                                                       \
    }

#endif  // ORMXX_INTERNAL_MACROS_H
