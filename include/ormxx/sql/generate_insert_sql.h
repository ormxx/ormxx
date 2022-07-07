#ifndef ORMXX_SQL_GENERATE_INSERT_H
#define ORMXX_SQL_GENERATE_INSERT_H

#include <string>
#include <vector>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../internal/field_to_string.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../internal/struct_schema_entrance_options.h"
#include "../types_check/has_ormxx_inject.h"

namespace ormxx {

namespace internal {

class GenerateInsertSQLUtility {
public:
    template <typename T>
    static std::tuple<std::string, std::string> GetFieldNameAndValue(T* t) {
        const auto& is_set_map = InjectEntrance::GetIsSetMap(t);

        std::string field_name_sql_string = "";
        std::string field_value_sql_string = "";

        auto options = internal::StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitForEach().Build();
        internal::InjectEntrance::StructSchemaEntrance(
                t,
                options,
                [&is_set_map, &field_name_sql_string, &field_value_sql_string](auto&& field, auto&& options) {
                    if (!is_set_map.count(options.origin_field_name) ||
                        is_set_map.at(options.origin_field_name) == false) {
                        return;
                    }

                    field_name_sql_string += fmt::format("`{}`, ", options.field_name);
                    field_value_sql_string += fmt::format("{}, ", internal::FieldToString(field));
                });

        if (!field_name_sql_string.empty()) {
            field_name_sql_string.pop_back();
            field_name_sql_string.pop_back();
        }

        if (!field_value_sql_string.empty()) {
            field_value_sql_string.pop_back();
            field_value_sql_string.pop_back();
        }

        return std::make_tuple(field_name_sql_string, field_value_sql_string);
    }
};

}  // namespace internal

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<std::string> GenerateInsertSQL(T* t) {
    const auto table_options = internal::InjectEntrance::GetTableOptions(t);
    std::string sql = "";

    auto [field_name_sql_string, field_value_sql_string] = internal::GenerateInsertSQLUtility::GetFieldNameAndValue(t);

    sql += fmt::format("INSERT INTO `{}` ({}) VALUES ({});",
                       table_options.table_name,
                       field_name_sql_string,
                       field_value_sql_string);

    return sql;
}

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<std::string> GenerateInsertSQL(const std::vector<T>* t_vector) {
    if (t_vector->empty()) {
        return Result::Builder(Result::ErrorCode::GenerateSQLError)
                .WithErrorMessage(fmt::format("insert list is empty"))
                .Build();
    }

    if (t_vector->size() == 1) {
        return GenerateInsertSQL(&t_vector->front());
    }

    std::string sql = "";

    const auto table_options = internal::InjectEntrance::GetTableOptions<T>(nullptr);

    auto [first_field_name_sql_string, first_field_value_sql_string] =
            internal::GenerateInsertSQLUtility::GetFieldNameAndValue(&t_vector->front());

    sql += fmt::format("INSERT INTO `{}` ({}) VALUES\n ({})",
                       table_options.table_name,
                       first_field_name_sql_string,
                       first_field_value_sql_string);

    for (size_t i = 1; i < t_vector->size(); i++) {
        auto [field_name_sql_string, field_value_sql_string] =
                internal::GenerateInsertSQLUtility::GetFieldNameAndValue(&t_vector->at(i));

        if (field_name_sql_string != first_field_name_sql_string) {
            return Result::Builder(Result::ErrorCode::GenerateSQLError)
                    .WithErrorMessage(fmt::format(
                            "insert list field name is not same. [first_field_name_sql_string: {}] [current_field_name_sql_string: {}]",
                            first_field_name_sql_string,
                            field_name_sql_string))
                    .Build();
        }

        sql += fmt::format(",\n ({})", field_value_sql_string);
    }

    sql += ";\n";

    return sql;
}

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<std::string> GenerateInsertSQL(std::vector<T>* t_vector) {
    return GenerateInsertSQL(static_cast<const std::vector<T>*>(t_vector));
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_INSERT_H
