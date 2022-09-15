#ifndef ORMXX_INTERNAL_QUERY_FIELDS_BUILDER_H
#define ORMXX_INTERNAL_QUERY_FIELDS_BUILDER_H

#include <string>

#include "../options/field_type.h"

namespace ormxx::internal {

template <typename T>
class QueryFieldsBuilder {
public:
    QueryFieldsBuilder() = default;

public:
private:
    std::string origin_field_name{""};
    std::string field_name{""};
    FieldTypeStruct field_type{};
};

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_QUERY_FIELDS_BUILDER_H
