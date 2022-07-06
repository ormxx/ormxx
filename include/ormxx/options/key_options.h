#ifndef ORMXX_OPTIONS_KEY_OPTIONS_H
#define ORMXX_OPTIONS_KEY_OPTIONS_H

#include <string>
#include <vector>

namespace ormxx {

struct KeyOptions {
public:
    enum class KeyType {
        PRIMARY,
        UNIQUE,
        INDEX,
    };

    enum class EngineType {
        BTREE,
    };

public:
    KeyType key_type{KeyType::PRIMARY};
    EngineType engine_type{EngineType::BTREE};
    std::string key_name{""};
    std::vector<std::string> field_name{};

public:
    static std::string KeyTypePrefixStr(KeyType key_type) {
        switch (key_type) {
            case KeyType::PRIMARY:
                return "primary";
            case KeyType::UNIQUE:
                return "uniq";
            case KeyType::INDEX:
                return "idx";
            default:
                return "unknown";
        }
    }

    static std::string KeyTypeStr(KeyType key_type) {
        switch (key_type) {
            case KeyType::PRIMARY:
                return "PRIMARY KEY";
            case KeyType::UNIQUE:
                return "UNIQUE KEY";
            case KeyType::INDEX:
                return "INDEX";
            default:
                return "unknown";
        }
    }

    static std::string EngineTypePrefixStr(EngineType engine_type) {
        switch (engine_type) {
            case EngineType::BTREE:
                return "BTREE";
            default:
                return "unknown";
        }
    }

public:
    static auto KeyType(KeyType key_type) {
        return [key_type](auto& options) {
            options.key_type = key_type;
        };
    }

    static auto EngineType(EngineType engine_type) {
        return [engine_type](auto& options) {
            options.engine_type = engine_type;
        };
    }

    static auto KeyName(const std::string& key_name) {
        return [key_name](auto& options) {
            options.key_name = key_name;
        };
    }

    static auto Field(const std::vector<std::string>& field_name) {
        return [field_name](auto& options) {
            options.field_name = field_name;
        };
    }

    template <typename... Opt>
    static auto ApplyKeyOptions(KeyOptions& options, Opt&&... opts) {
        (std::forward<Opt>(opts)(options), ...);
        return options;
    }

    template <typename... Opt>
    static auto CreateKeyOptions(Opt&&... opts) {
        KeyOptions options;
        return ApplyKeyOptions(options, std::forward<Opt>(opts)...);
    }
};

}  // namespace ormxx

#endif  // ORMXX_OPTIONS_KEY_OPTIONS_H
