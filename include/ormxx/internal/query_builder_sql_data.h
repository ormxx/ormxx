#ifndef ORMXX_INTERNAL_QUERY_BUILDER_SQL_DATA_H
#define ORMXX_INTERNAL_QUERY_BUILDER_SQL_DATA_H

#include <string>

namespace ormxx::internal {

struct QueryBuilderSQLData {
    std::string sql_from{""};
    std::string sql_select{""};
    std::string sql_where{""};

    std::string sql_limit{""};
    std::string sql_offset{""};
};

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_QUERY_BUILDER_SQL_DATA_H
