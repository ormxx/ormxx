#pragma once

#include <string>

#include "ormxx/options/field_options.h"
#include "ormxx/options/key_options.h"
#include "ormxx/options/table_options.h"
#include "ormxx/ormxx.h"

namespace ormxx::test::model {

struct User {
    int ID;
    std::string Name{""};
    int Age{0};

    // clang-format off
    ORMXX_STRUCT_SCHEMA_DECLARE_BEGIN(User)
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(ID,
        FieldOptions::FieldType::BigIntUnsigned(),
        FieldOptions::FieldName("id"),
        FieldOptions::NotNull(),
        FieldOptions::AutoIncrement(),
        FieldOptions::Comment("id")
    )
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(Name,
        FieldOptions::FieldType::Varchar(255),
        FieldOptions::FieldName("name"),
        FieldOptions::NotNull(),
        FieldOptions::Comment("name")
    )
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(Age,
        FieldOptions::FieldType::IntUnsigned(),
        FieldOptions::FieldName("age"),
        FieldOptions::NotNull(),
        FieldOptions::Comment("age")
    )

    ORMXX_STRUCT_SCHEMA_DECLARE_KEY(
        KeyOptions::KeyType(KeyOptions::KeyType::PRIMARY),
        KeyOptions::FieldName({"ID"}),
        KeyOptions::EngineType(KeyOptions::EngineType::BTREE)
    )
    ORMXX_STRUCT_SCHEMA_DECLARE_KEY(
        KeyOptions::KeyType(KeyOptions::KeyType::INDEX),
        KeyOptions::FieldName({"Name", "Age"}),
        KeyOptions::EngineType(KeyOptions::EngineType::BTREE)
    )
    ORMXX_STRUCT_SCHEMA_DECLARE_END(
        TableOptions::OptionsRawSQLString("ENGINE = InnoDB CHARACTER SET = utf8mb4"),
        TableOptions::Comment("User")
    )
    // clang-format on
};

}  // namespace ormxx::test::model
