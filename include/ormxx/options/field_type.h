#ifndef ORMXX_OPTIONS_FIELD_TYPE_H
#define ORMXX_OPTIONS_FIELD_TYPE_H

#include <cstdint>
#include <string>

namespace ormxx::internal {

enum class DataBaseFieldType {
    TINYINT,
    TINYINT_UNSIGNED,
    SMALLINT,
    SMALLINT_UNSIGNED,
    MEDIUMINT,
    MEDIUMINT_UNSIGNED,
    INT,
    INT_UNSIGNED,
    BIGINT,
    BIGINT_UNSIGNED,

    BOOLEAN,

    FLOAT,
    DOUBLE,
    DECIMAL,

    DATE,
    YEAR,
    TIME,
    DATETIME,
    TIMESTAMP,

    CHAR,
    VARCHAR,

    TINYTEXT,
    TEXT,
    MEDIUMTEXT,
    LONGTEXT,

    TINYBLOB,
    BLOB,
    MEDIUMBLOB,
    LONGBLOB,

    UNKNOWN,
};

enum class CXXFieldType {
    BOOLEAN,
    INT,
    UINT,
    INT64,
    UINT64,
    DOUBLE,
    STRING,

    UNKNOWN,
};

struct FieldTypeStruct {
    DataBaseFieldType data_base_field_type{DataBaseFieldType::UNKNOWN};
    CXXFieldType cxx_field_type{CXXFieldType::UNKNOWN};
    std::string data_base_field_type_string{""};
};

}  // namespace ormxx::internal

#endif  // ORMXX_OPTIONS_FIELD_TYPE_H
