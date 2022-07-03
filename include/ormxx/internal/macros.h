#ifndef ORMXX_INTERNAL_MACROS_H
#define ORMXX_INTERNAL_MACROS_H

#include "../types_check/has_ormxx_external_struct_schema_entrance.h"
#include "../types_check/has_ormxx_struct_schema_entrance.h"

#define ORMXX_STR(x) #x

#define ORMXX_STRUCT_SCHEMA_DECLARE_BEGIN(Struct)                                                                      \
private:                                                                                                               \
    friend class ::ormxx::has_ormxx_struct_schema_entrance<Struct>;                                                    \
    friend class ::ormxx::has_ormxx_struct_schema_entrance<const Struct>;                                              \
    friend class ::ormxx::internal::StructInjectEntranceClass;                                                         \
                                                                                                                       \
    template <typename T, std::enable_if_t<std::is_same_v<Struct, T> || std::is_same_v<const Struct, T>, bool> = true, \
            typename Func>                                                                                             \
    static void __ORMXX_StructSchemaEntrance(T* s, Func&& func) {
//
#define ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(field, ...)                                                            \
    {                                                                                                            \
        auto options =                                                                                           \
                ::ormxx::internal::CreateEntranceSchemaOptions(s, &(s->field), ORMXX_STR(field), ##__VA_ARGS__); \
        func(&(s->field), options);                                                                              \
    }

#define ORMXX_STRUCT_SCHEMA_DECLARE_END }

#define ORMXX_EXTERNAL_STRUCT_SCHEMA_DECLARE_BEGIN(Struct)                                                             \
    template <typename T, std::enable_if_t<std::is_same_v<Struct, T> || std::is_same_v<const Struct, T>, bool> = true, \
            typename Func>                                                                                             \
    static auto __ORMXXExternal_StructSchemaEntrance(T* s, Func&& func) {
//
#define ORMXX_EXTERNAL_STRUCT_SCHEMA_DECLARE_FIELD(field, ...) ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(field, ##__VA_ARGS__)

#define ORMXX_EXTERNAL_STRUCT_SCHEMA_DECLARE_END }

#endif  // ORMXX_INTERNAL_MACROS_H
