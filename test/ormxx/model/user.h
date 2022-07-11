#pragma once

#include <string>

#include "ormxx/ormxx.h"

namespace ormxx::test::model {

struct User {
    uint64_t ID;
    std::string Name{""};
    uint32_t Age{0};

    std::string UpdateTimestamp{""};
    std::string InsertTimestamp{""};

    ORMXX_STRUCT_SCHEMA_DECLARE_BEGIN(User, ID, Name, Age, UpdateTimestamp, InsertTimestamp)
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(ID,
                                      FieldOptions::FieldType::BigIntUnsigned(),
                                      FieldOptions::FieldName("id"),
                                      FieldOptions::NotNull(),
                                      FieldOptions::AutoIncrement(),
                                      FieldOptions::Comment("id"))
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(Name,
                                      FieldOptions::FieldType::Varchar(255),
                                      FieldOptions::FieldName("name"),
                                      FieldOptions::NotNull(),
                                      FieldOptions::Comment("name"))
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(Age,
                                      FieldOptions::FieldType::IntUnsigned(),
                                      FieldOptions::FieldName("age"),
                                      FieldOptions::NotNull(),
                                      FieldOptions::Comment("age"))

    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(UpdateTimestamp,
                                      FieldOptions::FieldType::Timestamp(6),
                                      FieldOptions::FieldName("update_timestamp"),
                                      FieldOptions::NotNull(),
                                      FieldOptions::Default("CURRENT_TIMESTAMP(6)"),
                                      FieldOptions::RawSQL("ON UPDATE CURRENT_TIMESTAMP(6)"),
                                      FieldOptions::Comment("update_timestamp"))
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(InsertTimestamp,
                                      FieldOptions::FieldType::Timestamp(6),
                                      FieldOptions::FieldName("insert_timestamp"),
                                      FieldOptions::NotNull(),
                                      FieldOptions::Default("CURRENT_TIMESTAMP(6)"),
                                      FieldOptions::Comment("insert_timestamp"))

    ORMXX_STRUCT_SCHEMA_DECLARE_KEY(KeyOptions::KeyType::PRIMARY,
                                    KeyOptions::Field({"ID"}),
                                    KeyOptions::EngineType(KeyOptions::EngineType::BTREE))
    ORMXX_STRUCT_SCHEMA_DECLARE_KEY(KeyOptions::KeyType::INDEX,
                                    KeyOptions::Field({"Name", "Age"}),
                                    KeyOptions::EngineType(KeyOptions::EngineType::BTREE))
    ORMXX_STRUCT_SCHEMA_DECLARE_END(TableOptions::TableName("user"),
                                    TableOptions::RawSQL("ENGINE = InnoDB CHARACTER SET = utf8mb4"),
                                    TableOptions::Comment("User"))
};

}  // namespace ormxx::test::model
