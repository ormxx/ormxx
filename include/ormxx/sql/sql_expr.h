#ifndef ORMXX_SQL_SQL_EXPR_H
#define ORMXX_SQL_SQL_EXPR_H

#include <string>

#include "../interface/sql_statement.h"

namespace ormxx::internal {

struct SQLExpr {
    SQLStatement sql_from{""};
    SQLStatement sql_select{""};
    SQLStatement sql_where{""};

    SQLStatement sql_order{""};
    SQLStatement sql_limit{""};
    SQLStatement sql_offset{""};
};

}  // namespace ormxx::internal

#endif  // ORMXX_SQL_SQL_EXPR_H
