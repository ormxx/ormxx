#ifndef ORMXX_SQL_GENERATE_CREATE_TABLE_SQL_H
#define ORMXX_SQL_GENERATE_CREATE_TABLE_SQL_H

#include <string>
#include <unordered_map>

#include "fmt/core.h"

#include "../interface/result.h"
#include "../internal/field_to_string.h"
#include "../internal/inject_entrance.h"
#include "../internal/struct_schema_entrance_options.h"
#include "../options/key_options.h"
#include "../options/table_options.h"
#include "../types_check/has_ormxx_inject.h"

namespace ormxx {

template <typename T, std::enable_if_t<internal::has_ormxx_inject_v<T>, bool> = true>
ResultOr<std::string> GenerateCreateTableSQL() {
    const T t = T{};
    const auto table_options = internal::InjectEntrance::GetTableOptions(&t);

    std::string sql = "\n";

    sql += fmt::format("CREATE TABLE `{}` (\n", table_options.table_name);

    std::unordered_map<std::string, std::string> origin_field_name_map_field_name;

    int ix = 0;

    {
        auto options = internal::StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitForEach().Build();
        internal::InjectEntrance::StructSchemaEntrance(
                &t, options, [&sql, &ix, &origin_field_name_map_field_name](auto &&field, auto &&options) {
                    if (ix > 0) {
                        sql += ",\n";
                    }

                    ++ix;

                    origin_field_name_map_field_name[options.origin_field_name] = options.field_name;

                    std::string field_sql = "";
                    field_sql +=
                            fmt::format("`{}` {}", options.field_name, options.field_type.data_base_field_type_string);

                    if (options.not_null) {
                        field_sql += " NOT NULL";

                        if (!options.auto_increment && options.custom_default_value_sql_string.empty()) {
                            field_sql += fmt::format(" DEFAULT {}", internal::FieldToString(field));
                        }
                    } else if (options.custom_default_value_sql_string.empty()) {
                        field_sql += " DEFAULT NULL";
                    }

                    if (!options.custom_default_value_sql_string.empty()) {
                        field_sql += fmt::format(" DEFAULT {}", options.custom_default_value_sql_string);
                    }

                    if (options.auto_increment) {
                        field_sql += " AUTO_INCREMENT";
                    }

                    if (!options.options_raw_sql_string.empty()) {
                        field_sql += fmt::format(" {}", options.options_raw_sql_string);
                    }

                    if (!options.comment.empty()) {
                        field_sql += fmt::format(" COMMENT '{}'", options.comment);
                    }

                    sql += fmt::format("    {}", field_sql);
                });
    }

    {
        Result res;

        auto options = internal::StructSchemaEntranceOptionsBuilder().WithVisitKey().WithVisitForEach().Build();
        internal::InjectEntrance::StructSchemaEntrance(
                &t, options, [&sql, &ix, &origin_field_name_map_field_name, &res](const KeyOptions &options) {
                    if (!res.IsOK()) {
                        return;
                    }

                    if (ix > 0) {
                        sql += ",\n";
                    }

                    ++ix;

                    std::string key_sql = "";
                    key_sql += KeyOptions::KeyTypeStr(options.key_type);

                    if (options.key_type != KeyOptions::KeyType::PRIMARY) {
                        if (!options.key_name.empty()) {
                            key_sql += fmt::format(" `{}`", options.key_name);
                        } else {
                            std::string key_name = KeyOptions::KeyTypePrefixStr(options.key_type);
                            for (const auto &field_name : options.field_name) {
                                if (origin_field_name_map_field_name.count(field_name) == 0) {
                                    res = Result::Builder(Result::ErrorCode::SchemaDeclareError)
                                                  .WithErrorMessage(fmt::format(
                                                          "field name not found. [field name: `{}`]", field_name))
                                                  .Build();
                                    return;
                                }

                                key_name += fmt::format("_{}", origin_field_name_map_field_name[field_name]);
                            }

                            key_sql += fmt::format(" `{}`", key_name);
                        }
                    }

                    {
                        key_sql += " (";

                        for (size_t i = 0; i < options.field_name.size(); i++) {
                            if (i > 0) {
                                key_sql += ", ";
                            }

                            if (origin_field_name_map_field_name.count(options.field_name[i]) == 0) {
                                res = Result::Builder(Result::ErrorCode::SchemaDeclareError)
                                              .WithErrorMessage(fmt::format("field name not found. [field name: `{}`]",
                                                                            options.field_name[i]))
                                              .Build();
                                return;
                            }

                            key_sql += fmt::format("`{}`", origin_field_name_map_field_name[options.field_name[i]]);
                        }

                        key_sql += ")";
                    }

                    key_sql += fmt::format(" USING {}", KeyOptions::EngineTypePrefixStr(options.engine_type));

                    sql += fmt::format("    {}", key_sql);
                });

        if (!res.IsOK()) {
            return res;
        }
    }

    sql += "\n)";

    if (!table_options.options_raw_sql_string.empty()) {
        sql += fmt::format(" {}", table_options.options_raw_sql_string);
    }

    if (!table_options.comment.empty()) {
        sql += fmt::format(" COMMENT = '{}'", table_options.comment);
    }

    sql += ";\n";

    return sql;
}

};  // namespace ormxx

#endif  // ORMXX_SQL_GENERATE_CREATE_TABLE_SQL_H
