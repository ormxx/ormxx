#ifndef ORMXX_SQL_GENERATE_UPDATE_SQL_STATEMENT_H
#define ORMXX_SQL_GENERATE_UPDATE_SQL_STATEMENT_H

#include "../interface/result.h"
#include "../interface/sql_statement.h"
#include "../internal/field_to_sql_statement_field_value.h"
#include "../internal/inject_utility.h"
#include "../types_check/has_ormxx_inject.h"

namespace ormxx {

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<SQLStatement> GenerateUpdateSQLStatement(T* t) {
    auto primary_key_filed_name_res = internal::InjectUtility::GetPrimaryKeyFieldName<T>();
    if (!primary_key_filed_name_res.IsOK()) {
        return primary_key_filed_name_res;
    }

    const auto primary_key_field_name = std::move(primary_key_filed_name_res.Value());
    const auto table_options = internal::InjectEntrance::GetTableOptions(t);

    SQLStatement sql_statement{};
    auto& sql_string = sql_statement.SQLString();

    sql_statement.AppendSQLString(fmt::format("UPDATE `{}` SET ", table_options.table_name));

    {
        const auto options =
                internal::StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitFieldByIsSet().Build();
        internal::InjectEntrance::StructSchemaEntrance(t, options, [&sql_statement](auto&& field, auto&& options) {
            sql_statement.AppendSQLString(fmt::format("`{}` = ?, ", options.field_name));

            auto f = SQLStatement::Field{};
            f.field_type = options.field_type;
            f.value = internal::FieldToSQLStatementFieldValue(field);

            sql_statement.AppendField(f);
        });
    }

    if (sql_string.length() >= 2 && sql_string.substr(sql_string.length() - 2) == ", ") {
        sql_string.pop_back();
        sql_string.pop_back();
    } else {
        auto res = Result::Builder(Result::ErrorCode::GenerateSQLError)
                           .WithErrorMessage(fmt::format("update field empty"))
                           .Build();
        RESULT_DIRECT_RETURN(res);
    }

    sql_statement.AppendSQLString(" WHERE ");

    {
        const auto options = internal::StructSchemaEntranceOptionsBuilder()
                                     .WithVisitField()
                                     .WithVisitFieldByName(primary_key_field_name)
                                     .Build();
        internal::InjectEntrance::StructSchemaEntrance(t, options, [&sql_statement](auto&& field, auto&& options) {
            sql_statement.AppendSQLString(fmt::format("`{}` = ?", options.field_name));

            auto f = SQLStatement::Field{};
            f.field_type = options.field_type;
            f.value = internal::FieldToSQLStatementFieldValue(field);

            sql_statement.AppendField(f);
        });
    }

    sql_statement.AppendSQLString(";");

    return sql_statement;
}

}  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_UPDATE_SQL_STATEMENT_H
