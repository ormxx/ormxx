#ifndef ORMXX_OPTIONS_FIELD_OPTIONS_H
#define ORMXX_OPTIONS_FIELD_OPTIONS_H

#include <optional>
#include <string>
#include <string_view>

#include "fmt/core.h"

#include "./field_type.h"

namespace ormxx {

namespace internal {

template <typename T, typename F>
struct FieldOptionsStruct {
    std::string origin_field_name{""};
    F struct_field_type;

    std::string field_name{""};
    FieldTypeStruct field_type;
    std::string comment{""};
    bool not_null{false};
    bool auto_increment{false};
    // not for now
    std::optional<T> default_value{std::nullopt};
};

}  // namespace internal

class FieldOptions {
public:
    static auto FieldName(const std::string& field_name) {
        return [field_name](auto& options) {
            options.field_name = field_name;
        };
    }

    class FieldType {
    public:
        static auto TinyInt(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::TINYINT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::INT;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("TINYINT({})", width);
                } else {
                    field_type_struct.data_base_field_type_string = "TINYINT";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto TinyIntUnsigned(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::TINYINT_UNSIGNED;
                field_type_struct.cxx_field_type = internal::CXXFieldType::UINT;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("TINYINT({}) UNSIGNED", width);
                } else {
                    field_type_struct.data_base_field_type_string = "TINYINT UNSIGNED";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto SmallInt(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::SMALLINT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::INT;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("SMALLINT({})", width);
                } else {
                    field_type_struct.data_base_field_type_string = "SMALLINT";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto SmallIntUnsigned(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::SMALLINT_UNSIGNED;
                field_type_struct.cxx_field_type = internal::CXXFieldType::UINT;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("SMALLINT({}) UNSIGNED", width);
                } else {
                    field_type_struct.data_base_field_type_string = "SMALLINT UNSIGNED";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto MediumInt(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::MEDIUMINT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::INT;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("MEDIUMINT({})", width);
                } else {
                    field_type_struct.data_base_field_type_string = "MEDIUMINT";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto MediumIntUnsigned(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::MEDIUMINT_UNSIGNED;
                field_type_struct.cxx_field_type = internal::CXXFieldType::UINT;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("MEDIUMINT({}) UNSIGNED", width);
                } else {
                    field_type_struct.data_base_field_type_string = "MEDIUMINT UNSIGNED";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto Int(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::INT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::INT;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("INT({})", width);
                } else {
                    field_type_struct.data_base_field_type_string = "INT";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto IntUnsigned(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::INT_UNSIGNED;
                field_type_struct.cxx_field_type = internal::CXXFieldType::UINT;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("INT({}) UNSIGNED", width);
                } else {
                    field_type_struct.data_base_field_type_string = "INT UNSIGNED";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto BigInt(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::BIGINT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::INT64;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("BIGINT({})", width);
                } else {
                    field_type_struct.data_base_field_type_string = "BIGINT";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto BigIntUnsigned(int width = -1) {
            return [width](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::BIGINT_UNSIGNED;
                field_type_struct.cxx_field_type = internal::CXXFieldType::UINT64;

                if (width != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("BIGINT({}) UNSIGNED", width);
                } else {
                    field_type_struct.data_base_field_type_string = "BIGINT UNSIGNED";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto Boolean() {
            return [](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::BOOLEAN;
                field_type_struct.cxx_field_type = internal::CXXFieldType::BOOLEAN;
                field_type_struct.data_base_field_type_string = "BOOLEAN";
                options.field_type = field_type_struct;
            };
        }

        // [0, 23]
        static auto Float(int precision = -1) {
            return [precision](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::FLOAT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::DOUBLE;

                if (precision != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("FLOAT({})", precision);
                } else {
                    field_type_struct.data_base_field_type_string = "FLOAT";
                }

                options.field_type = field_type_struct;
            };
        }

        // [24,53]
        static auto Double(int precision = -1) {
            return [precision](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::DOUBLE;
                field_type_struct.cxx_field_type = internal::CXXFieldType::DOUBLE;

                if (precision != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("DOUBLE({})", precision);
                } else {
                    field_type_struct.data_base_field_type_string = "DOUBLE";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto Decimal(int m = -1, int d = -1) {
            return [m, d](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::DECIMAL;
                field_type_struct.cxx_field_type = internal::CXXFieldType::DOUBLE;

                if (m != -1 && d != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("DECIMAL({}, {})", m, d);
                } else if (m != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("DECIMAL({})", m, d);
                } else {
                    field_type_struct.data_base_field_type_string = "DECIMAL";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto hDate() {
            return [](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::DATE;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;
                field_type_struct.data_base_field_type_string = "DATE";
                options.field_type = field_type_struct;
            };
        }

        static auto Year() {
            return [](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::YEAR;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;
                field_type_struct.data_base_field_type_string = "YEAR";
                options.field_type = field_type_struct;
            };
        }

        // [0, 6]
        static auto Time(int precision = -1) {
            return [precision](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::TIME;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;

                if (precision != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("TIME({})", precision);
                } else {
                    field_type_struct.data_base_field_type_string = "TIME";
                }

                options.field_type = field_type_struct;
            };
        }

        // [0, 6]
        static auto DateTime(int precision = -1) {
            return [precision](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::DATETIME;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;

                if (precision != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("DATETIME({})", precision);
                } else {
                    field_type_struct.data_base_field_type_string = "DATETIME";
                }

                options.field_type = field_type_struct;
            };
        }

        // [0, 6]
        static auto Timestamp(int precision = -1) {
            return [precision](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::TIMESTAMP;
                field_type_struct.cxx_field_type = internal::CXXFieldType::UINT64;

                if (precision != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("TIMESTAMP({})", precision);
                } else {
                    field_type_struct.data_base_field_type_string = "TIMESTAMP";
                }

                options.field_type = field_type_struct;
            };
        }

        // [0, 255]
        static auto Char(int length = -1) {
            return [length](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::CHAR;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;

                if (length != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("CHAR({})", length);
                } else {
                    field_type_struct.data_base_field_type_string = "CHAR";
                }

                options.field_type = field_type_struct;
            };
        }

        // [0, 65535]
        static auto Varchar(int length = -1) {
            return [length](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::VARCHAR;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;

                if (length != -1) {
                    field_type_struct.data_base_field_type_string = fmt::format("VARCHAR({})", length);
                } else {
                    field_type_struct.data_base_field_type_string = "VARCHAR";
                }

                options.field_type = field_type_struct;
            };
        }

        static auto TinyText() {
            return [](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::TINYTEXT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;
                field_type_struct.data_base_field_type_string = "TINYTEXT";
                options.field_type = field_type_struct;
            };
        }

        static auto Text() {
            return [](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::TEXT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;
                field_type_struct.data_base_field_type_string = "TEXT";
                options.field_type = field_type_struct;
            };
        }

        static auto MediumText() {
            return [](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::MEDIUMTEXT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;
                field_type_struct.data_base_field_type_string = "MEDIUMTEXT";
                options.field_type = field_type_struct;
            };
        }

        static auto LongText() {
            return [](auto& options) {
                internal::FieldTypeStruct field_type_struct;
                field_type_struct.data_base_field_type = internal::DataBaseFieldType::LONGTEXT;
                field_type_struct.cxx_field_type = internal::CXXFieldType::STRING;
                field_type_struct.data_base_field_type_string = "LONGTEXT";
                options.field_type = field_type_struct;
            };
        }
    };

    static auto Comment(const std::string& comment) {
        return [comment](auto& options) {
            options.comment = comment;
        };
    }

    static auto NotNull(bool not_null = true) {
        return [not_null](auto& options) {
            options.not_null = not_null;
        };
    }

    static auto AutoIncrement(bool auto_increment = true) {
        return [auto_increment](auto& options) {
            options.auto_increment = auto_increment;
        };
    }

    template <typename T, typename F, typename... Opt>
    static auto ApplyFieldOptions(internal::FieldOptionsStruct<T, F>& options, Opt&&... opts) {
        (std::forward<Opt>(opts)(options), ...);
        return options;
    }

    template <typename T, typename F, typename... Opt>
    static auto CreateFieldOptions(Opt&&... opts) {
        internal::FieldOptionsStruct<T, F> options;
        return ApplyFieldOptions(options, std::forward<Opt>(opts)...);
    }
};

}  // namespace ormxx

#endif  // ORMXX_OPTIONS_FIELD_OPTIONS_H
