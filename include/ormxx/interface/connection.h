#ifndef ORMXX_INTERFACE_CONNECTION_H
#define ORMXX_INTERFACE_CONNECTION_H

#include <memory>

#include "./execute_result.h"
#include "./result.h"

namespace ormxx {

class Connection {
public:
    Connection() {}
    virtual ~Connection() {}

    virtual bool ReConnect() = 0;

    virtual void Close() = 0;

    virtual Result BeginTransaction() = 0;
    virtual Result Commit() = 0;
    virtual Result Rollback() = 0;

    virtual ResultOr<std::unique_ptr<ExecuteResult>> Execute(const std::string& sql) = 0;

    virtual ResultOr<std::unique_ptr<ExecuteResult>> ExecuteQuery(const std::string& sql) = 0;

    virtual ResultOr<std::unique_ptr<ExecuteResult>> ExecuteUpdate(const std::string& sql) = 0;
};

}  // namespace ormxx

#endif  // ORMXX_INTERFACE_CONNECTION_H
