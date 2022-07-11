#ifndef ORMXX_SQL_SQL_UTILITY_H
#define ORMXX_SQL_SQL_UTILITY_H

#include <string>

#include "fmt/core.h"

#include "../internal/field_to_string.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../internal/result_to_field.h"
#include "../types_check/has_ormxx_inject.h"

namespace ormxx::internal {

class SQLUtility {
public:
    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    static std::string GenerateAllFieldNameSelectSQLString(T* t) {
        const auto table_options = internal::InjectEntrance::GetTableOptions(t);
        const auto field_name_vector = internal::InjectUtility::GetAllFieldName(t);

        std::string sql = "";

        for (size_t i = 0; i < field_name_vector.size(); ++i) {
            if (i) {
                sql += ", ";
            }

            sql += fmt::format("`{}`.`{}`", table_options.table_name, field_name_vector[i]);
        }

        return sql;
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    static std::string GenerateWhereSQLString(T* t) {
        const auto table_options = internal::InjectEntrance::GetTableOptions(t);

        std::string sql = "";

        auto options = internal::StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitFieldByIsSet().Build();
        internal::InjectEntrance::StructSchemaEntrance(t, options, [&sql](auto&& field, auto&& options) {
            std::string prefix = sql.empty() ? "" : " AND ";
            sql += fmt::format("{}`{}` = {}", prefix, options.field_name, internal::FieldToString(field));
        });

        return sql;
    }
};

}  // namespace ormxx::internal

#endif  // ORMXX_SQL_SQL_UTILITY_H
