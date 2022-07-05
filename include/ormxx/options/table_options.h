#ifndef ORMXX_INTERNAL_TABLE_OPTIONS_H
#define ORMXX_INTERNAL_TABLE_OPTIONS_H

#include <string>

namespace ormxx {

struct TableOptions {
    std::string origin_struct_name{""};
    std::string table_name{""};
    std::string comment{""};
    std::string character{"utf8mb4"};
    std::string engine{"InnoDB"};

public:
    static auto WithTableName(const std::string& table_name) {
        return [table_name](auto& options) {
            options.table_name = table_name;
        };
    }

    static auto WithComment(const std::string& comment) {
        return [comment](auto& options) {
            options.comment = comment;
        };
    }

    static auto WithCharacter(const std::string& character) {
        return [character](auto& options) {
            options.character = character;
        };
    }

    static auto WithEngine(const std::string& engine) {
        return [engine](auto& options) {
            options.engine = engine;
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
