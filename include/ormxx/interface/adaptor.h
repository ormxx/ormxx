#ifndef ORMXX_INTERFACE_ADAPTOR_H
#define ORMXX_INTERFACE_ADAPTOR_H

#include "./connection.h"
#include "./result.h"

namespace ormxx {

class Adaptor {
public:
    enum class ConnectionType {
        READ,
        WRITE,
    };

public:
    Adaptor() {}
    virtual ~Adaptor() {}

    virtual ResultOr<Connection*> GetConnection(ConnectionType type = ConnectionType::WRITE) = 0;

    virtual ResultOr<Connection*> GetWriteConnection() {
        return GetConnection(ConnectionType::WRITE);
    }

    virtual ResultOr<Connection*> GetReadConnection() {
        return GetConnection(ConnectionType::READ);
    }
};

}  // namespace ormxx

#endif  // ORMXX_INTERFACE_ADAPTOR_H
