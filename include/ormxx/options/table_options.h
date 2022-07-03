#ifndef ORMXX_INTERNAL_TABLE_OPTIONS_H
#define ORMXX_INTERNAL_TABLE_OPTIONS_H

#include <string>

namespace ormxx {

struct TableOptions {
    std::string origin_struct_name{""};
    std::string table_name{""};

public:
    static auto WithTableName(const std::string& table_name) {
        return [table_name](auto& options) {
            options.table_name = table_name;
        };
    }

    template <typename... Opt>
    static auto ApplyTableOptions(TableOptions& options, Opt&&... opts) {
        (std::forward<Opt>(opts)(options), ...);
        return options;
    }

    template <typename T, typename... Opt>
    static auto CreateTableOptions(Opt&&... opts) {
        TableOptions options;
        return ApplySchemaOptions(options, std::forward<Opt>(opts)...);
    }
};

}  // namespace ormxx

#endif  // ORMXX_INTERNAL_TABLE_OPTIONS_H
