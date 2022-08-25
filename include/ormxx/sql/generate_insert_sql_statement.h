#ifndef ORMXX_SQL_GENERATE_INSERT_SQL_STATEMENT_H
#define ORMXX_SQL_GENERATE_INSERT_SQL_STATEMENT_H

#include <string>
#include <vector>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../interface/sql_statement.h"
#include "../internal/field_to_sql_statement_field_value.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../internal/struct_schema_entrance_options.h"
#include "../types_check/has_ormxx_inject.h"

namespace ormxx {

namespace internal {

class GenerateInsertSQLStatementUtility {
public:
    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
    static std::tuple<SQLStatement, SQLStatement> GetFieldNameAndValueWithSQLStatement(T* t) {
        const auto& is_set_map = InjectEntrance::GetIsSetMap(t);

        auto field_name = SQLStatement();
        auto field_value = SQLStatement();

        std::string field_name_sql_string = "";
        std::string field_value_sql_string = "";

        auto options = internal::StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitForEach().Build();
        internal::InjectEntrance::StructSchemaEntrance(
                t,
                options,
                [&is_set_map, &field_name, &field_name_sql_string, &field_value, &field_value_sql_string](
                        auto&& field, auto&& options) {
                    if (!is_set_map.count(options.origin_field_name) ||
                        is_set_map.at(options.origin_field_name) == false) {
                        return;
                    }

                    field_name_sql_string += fmt::format("`{}`, ", options.field_name);
                    field_value_sql_string += "?, ";

                    auto f = SQLStatement::Field{};
                    f.field_type = options.field_type;
                    f.value = internal::FieldToSQLStatementFieldValue(field);

                    field_value.AppendField(f);
                });

        if (!field_name_sql_string.empty()) {
            field_name_sql_string.pop_back();
            field_name_sql_string.pop_back();
        }

        if (!field_value_sql_string.empty()) {
            field_value_sql_string.pop_back();
            field_value_sql_string.pop_back();
        }

        field_name.SetSQLString(std::move(field_name_sql_string));
        field_value.SetSQLString(std::move(field_value_sql_string));

        return std::make_tuple(field_name, field_value);
    }
};

}  // namespace internal

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<SQLStatement> GenerateInsertSQLStatement(T* t) {
    const auto table_options = internal::InjectEntrance::GetTableOptions(t);

    auto sql_statement = SQLStatement{};

    auto [field_name_sql_statement, field_value_sql_statement] =
            internal::GenerateInsertSQLStatementUtility::GetFieldNameAndValueWithSQLStatement(t);

    sql_statement.AppendSQLString(fmt::format("INSERT INTO `{}` ({}) VALUES ({});",
                                              table_options.table_name,
                                              std::move(field_name_sql_statement.SQLString()),
                                              std::move(field_value_sql_statement.GetSQLString())));
    sql_statement.AppendFields(std::move(field_value_sql_statement.Fields()));

    return sql_statement;
}

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<SQLStatement> GenerateInsertSQLStatement(const std::vector<T>* t_vector) {
    if (t_vector->empty()) {
        return Result::Builder(Result::ErrorCode::GenerateSQLError)
                .WithErrorMessage(fmt::format("insert list is empty"))
                .Build();
    }

    if (t_vector->size() == 1) {
        return GenerateInsertSQLStatement(&t_vector->front());
    }

    auto sql_statement = SQLStatement{};

    const auto table_options = internal::InjectEntrance::GetTableOptions<T>(nullptr);

    auto [first_field_name_sql_statement, first_field_value_sql_statement] =
            internal::GenerateInsertSQLStatementUtility::GetFieldNameAndValueWithSQLStatement(&t_vector->front());

    sql_statement.AppendSQLString(fmt::format("INSERT INTO `{}` ({}) VALUES\n ({})",
                                              table_options.table_name,
                                              first_field_name_sql_statement.GetSQLString(),
                                              std::move(first_field_value_sql_statement.SQLString())));
    sql_statement.AppendFields(first_field_value_sql_statement.Fields());

    for (size_t i = 1; i < t_vector->size(); i++) {
        auto [field_name_sql_statement, field_value_sql_statement] =
                internal::GenerateInsertSQLStatementUtility::GetFieldNameAndValueWithSQLStatement(&t_vector->at(i));

        if (field_name_sql_statement.SQLString() != first_field_name_sql_statement.SQLString()) {
            return Result::Builder(Result::ErrorCode::GenerateSQLError)
                    .WithErrorMessage(fmt::format(
                            "insert list field name is not same. [first_field_name_sql_string: {}] [current_field_name_sql_string: {}]",
                            first_field_name_sql_statement.GetSQLString(),
                            field_name_sql_statement.GetSQLString()))
                    .Build();
        }

        sql_statement.AppendSQLString(fmt::format(",\n ({})", field_value_sql_statement.SQLString()));
        sql_statement.AppendFields(field_value_sql_statement.Fields());
    }

    sql_statement.AppendSQLString(";\n");

    return sql_statement;
}

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<SQLStatement> GenerateInsertSQLStatement(std::vector<T>* t_vector) {
    return GenerateInsertSQLStatement(static_cast<const std::vector<T>*>(t_vector));
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_INSERT_SQL_STATEMENT_H
