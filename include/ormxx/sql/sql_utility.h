#ifndef ORMXX_SQL_SQL_UTILITY_H
#define ORMXX_SQL_SQL_UTILITY_H

#include <string>

#include "fmt/core.h"

#include "../interface/sql_statement.h"
#include "../internal/field_builder.h"
#include "../internal/field_to_sql_statement_field_value.h"
#include "../internal/field_to_string.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../internal/result_to_field.h"
#include "../types_check/has_ormxx_inject.h"
#include "../types_check/is_field_builder.h"

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
    static SQLStatement GenerateWhereSQLStatement(T* t) {
        const auto table_options = internal::InjectEntrance::GetTableOptions(t);

        SQLStatement sql_statement{};

        auto options = internal::StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitFieldByIsSet().Build();
        internal::InjectEntrance::StructSchemaEntrance(t, options, [&sql_statement](auto&& field, auto&& options) {
            std::string prefix = sql_statement.GetSQLString().empty() ? "" : " AND ";

            auto f = SQLStatement::Field{};
            f.field_type = options.field_type;
            f.value = internal::FieldToSQLStatementFieldValue(field);

            sql_statement.AppendSQLString(fmt::format("{}`{}` = ?", std::move(prefix), options.field_name));
            sql_statement.AppendField(std::move(f));
        });

        return sql_statement;
    }

    template <typename... QueryFieldsBuilder>
    static SQLStatement GenerateWhereSQLStatement(QueryFieldsBuilder&&... q) {
        SQLStatement s{};

        const auto f = [&s](auto&& q) -> bool {
            std::string prefix = s.Empty() ? "" : " AND ";
            const auto& ss = getSQLStatementFromQueryFieldsBuilder(q);
            s.AppendSQLString(fmt::format("{}{}", prefix, ss.GetSQLString()));
            s.AppendFields(ss.GetFields());

            return true;
        };

        (f(std::forward<QueryFieldsBuilder>(q)) && ...);

        return s;
    }

    template <typename... QueryFieldsBuilder>
    static SQLStatement GenerateOrderSQLStatement(QueryFieldsBuilder&&... q) {
        SQLStatement s{};

        const auto f = [&s](auto&& q) -> bool {
            std::string prefix = s.Empty() ? "" : ", ";
            const auto& ss = getSQLStatementFromQueryFieldsBuilder(q);
            s.AppendSQLString(fmt::format("{}{}", prefix, ss.GetSQLString()));

            return true;
        };

        (f(std::forward<QueryFieldsBuilder>(q)) && ...);

        return s;
    }

    template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<std::decay_t<T>>, bool> = true>
    static ResultOr<SQLStatement> GenerateUpdateSetSQLStatement(const T& t) {
        SQLStatement s{};
        auto& sql_string = s.SQLString();

        {
            const auto o =
                    internal::StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitFieldByIsSet().Build();
            internal::InjectEntrance::StructSchemaEntrance(&t, o, [&s](auto&& field, auto&& options) {
                s.AppendSQLString(fmt::format("`{}` = ?, ", options.field_name));

                auto f = SQLStatement::Field{};
                f.field_type = options.field_type;
                f.value = internal::FieldToSQLStatementFieldValue(field);

                s.AppendField(f);
            });
        }

        if (sql_string.length() >= 2 && sql_string.substr(sql_string.length() - 2) == ", ") {
            sql_string.pop_back();
            sql_string.pop_back();
        } else {
            auto res = Result::Builder(Result::ErrorCode::GenerateSQLError)
                               .WithErrorMessage(fmt::format("update field is empty"))
                               .Build();
            RESULT_DIRECT_RETURN(res);
        }

        return s;
    }

    template <typename... FieldBuilder, std::enable_if_t<internal::is_field_builder_v<FieldBuilder...>, bool> = true>
    static ResultOr<SQLStatement> GenerateUpdateSetSQLStatement(FieldBuilder&&... field_builder) {
        SQLStatement s{};

        const auto f = [&s](auto&& field_builder) -> bool {
            std::string prefix = s.Empty() ? "" : ", ";

            const auto& ss = getSQLStatementFromQueryFieldsBuilder(field_builder);
            s.AppendSQLString(fmt::format("{}{}", prefix, ss.GetSQLString()));
            s.AppendFields(ss.GetFields());

            return true;
        };

        (f(std::forward<FieldBuilder>(field_builder)) && ...);

        return s;
    }

private:
    template <typename T>
    static const SQLStatement& getSQLStatementFromQueryFieldsBuilder(const FieldBuilder<T>& field_builder) {
        return field_builder.getSQLStatement();
    }
};

}  // namespace ormxx::internal

#endif  // ORMXX_SQL_SQL_UTILITY_H
