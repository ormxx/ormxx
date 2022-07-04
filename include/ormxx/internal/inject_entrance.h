#ifndef ORMXX_INTERNAL_INJECT_ENTRANCE_H
#define ORMXX_INTERNAL_INJECT_ENTRANCE_H

#include "../options/table_options.h"
#include "../types_check/common.h"
#include "../types_check/has_ormxx_external_get_table_options.h"
#include "../types_check/has_ormxx_external_struct_schema_entrance.h"
#include "../types_check/has_ormxx_get_table_options.h"
#include "../types_check/has_ormxx_struct_schema_entrance.h"

namespace ormxx::internal {

class InjectEntrance {
public:
    template <typename T>
    static ::ormxx::TableOptions GetTableOptions([[maybe_unused]] T* t) {
        if constexpr (has_ormxx_get_table_options_v<T>) {
            return T::__ORMXX_GetTableOptions();
        } else if constexpr (has_ormxx_external_get_table_options_v<T>) {
            return __ORMXXExternal_GetTableOptions(t);
        } else {
            static_assert(false_v<T>,
                    "T does not have T::__ORMXX_StructSchemaEntrance() member function or __ORMXXExternal_StructSchemaEntrance() external function");
        }
    }

    template <typename T, typename Func>
    static void StructSchemaEntrance(T* t, Func&& func) {
        if constexpr (has_ormxx_struct_schema_entrance_v<T>) {
            return T::__ORMXX_StructSchemaEntrance(t, func);
        } else if constexpr (has_ormxx_external_struct_schema_entrance_v<T>) {
            return __ORMXXExternal_StructSchemaEntrance(t, func);
        } else {
            static_assert(false_v<T>,
                    "T does not have T::__ORMXX_StructSchemaEntrance() member function or __ORMXXExternal_StructSchemaEntrance() external function");
        }
    }
};

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_INJECT_ENTRANCE_H
