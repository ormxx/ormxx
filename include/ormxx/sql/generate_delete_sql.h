#ifndef ORMXX_SQL_GENERATE_DELETE_SQL_H
#define ORMXX_SQL_GENERATE_DELETE_SQL_H

#include <string>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../internal/field_to_string.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../types_check/has_ormxx_inject.h"

namespace ormxx {

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<std::string> GenerateDeleteSQL(T* t) {
    auto primary_key_filed_name_res = internal::InjectUtility::GetPrimaryKeyFieldName<T>();
    if (!primary_key_filed_name_res.IsOK()) {
        return primary_key_filed_name_res;
    }

    const auto primary_key_field_name = std::move(primary_key_filed_name_res.Value());
    const auto table_options = internal::InjectEntrance::GetTableOptions(t);

    std::string sql = fmt::format("DELETE FROM `{}` WHERE ", table_options.table_name);

    {
        const auto options = internal::StructSchemaEntranceOptionsBuilder()
                                     .WithVisitField()
                                     .WithVisitFieldByName(primary_key_field_name)
                                     .Build();
        internal::InjectEntrance::StructSchemaEntrance(t, options, [&sql](auto&& field, auto&& options) {
            sql += fmt::format("`{}` = {}", options.field_name, internal::FieldToString(field));
        });
    }

    sql += ";";

    return sql;
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_DELETE_SQL_H
