#pragma once

#include <string>

#include "ormxx/internal/macros.h"
#include "ormxx/ormxx.h"

namespace ormxx::test::model {

struct User {
    int id;
    std::string name;
    int age;

    ORMXX_STRUCT_SCHEMA_DECLARE_BEGIN(User)
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(id)
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(name)
    ORMXX_STRUCT_SCHEMA_DECLARE_FIELD(age)
    ORMXX_STRUCT_SCHEMA_DECLARE_END
};

}  // namespace ormxx::test::model
