#ifndef ORMXX_INTERNAL_QUERY_BUILDER_SQL_DATA_H
#define ORMXX_INTERNAL_QUERY_BUILDER_SQL_DATA_H

#include <string>

#include "../interface/sql_statement.h"

namespace ormxx::internal {

struct QueryBuilderSQLData {
    SQLStatement sql_from{""};
    SQLStatement sql_select{""};
    SQLStatement sql_where{""};

    SQLStatement sql_order{""};
    SQLStatement sql_limit{""};
    SQLStatement sql_offset{""};
};

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_QUERY_BUILDER_SQL_DATA_H
