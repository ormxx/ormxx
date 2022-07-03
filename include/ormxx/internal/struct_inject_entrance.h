#ifndef ORMXX_INTERNAL_STRUCT_INJECT_ENTRANCE_H
#define ORMXX_INTERNAL_STRUCT_INJECT_ENTRANCE_H

#include "../types_check/common.h"
#include "../types_check/has_ormxx_external_struct_schema_entrance.h"
#include "../types_check/has_ormxx_struct_schema_entrance.h"

namespace ormxx::internal {

class StructInjectEntranceClass {
public:
    template <typename T, typename Func>
    void operator()(T* t, Func&& func) const {
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

static const auto StructInjectEntrance = StructInjectEntranceClass();

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_STRUCT_INJECT_ENTRANCE_H
