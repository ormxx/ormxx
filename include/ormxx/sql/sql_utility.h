#ifndef ORMXX_SQL_SQL_UTILITY_H
#define ORMXX_SQL_SQL_UTILITY_H

#include <string>

#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../types_check/has_ormxx_inject.h"

namespace ormxx::internal {

class SQLUtility {
public:
    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    static std::string GenerateSelectSQLString(T* t) {
        const auto table_options = internal::InjectEntrance::GetTableOptions(t);
        const auto field_name_vector = internal::InjectUtility::GetAllFieldName(t);

        std::string sql = "SELECT ";

        for (size_t i = 0; i < field_name_vector.size(); ++i) {
            if (i) {
                sql += ", ";
            }

            sql += fmt::format("`{}`.`{}`", table_options.table_name, field_name_vector[i]);
        }

        return sql;
    }
};

}  // namespace ormxx::internal

#endif  // ORMXX_SQL_SQL_UTILITY_H
