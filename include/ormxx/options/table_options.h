#ifndef ORMXX_OPTIONS_TABLE_OPTIONS_H
#define ORMXX_OPTIONS_TABLE_OPTIONS_H

#include <string>

namespace ormxx {

struct TableOptions {
    std::string origin_struct_name{""};
    std::string table_name{""};
    std::string comment{""};
    std::string options_raw_sql_string{""};

public:
    static auto TableName(const std::string& table_name) {
        return [table_name](auto& options) {
            options.table_name = table_name;
        };
    }

    static auto Comment(const std::string& comment) {
        return [comment](auto& options) {
            options.comment = comment;
        };
    }

    static auto OptionsRawSQLString(const std::string& options_raw_sql_string) {
        return [options_raw_sql_string](auto& options) {
            options.options_raw_sql_string = options_raw_sql_string;
        };
    }

    template <typename... Opt>
    static auto ApplyTableOptions(TableOptions& options, Opt&&... opts) {
        (std::forward<Opt>(opts)(options), ...);
        return options;
    }

    template <typename... Opt>
    static auto CreateTableOptions(Opt&&... opts) {
        TableOptions options;
        return ApplyTableOptions(options, std::forward<Opt>(opts)...);
    }
};

}  // namespace ormxx

#endif  // ORMXX_OPTIONS_TABLE_OPTIONS_H
