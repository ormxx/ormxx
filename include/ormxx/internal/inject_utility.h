#ifndef ORMXX_INTERNAL_INJECT_UTILITY_H
#define ORMXX_INTERNAL_INJECT_UTILITY_H

#include <string>
#include <tuple>
#include <vector>

#include "./field_to_string.h"
#include "./inject_entrance.h"
#include "./struct_schema_entrance_options.h"

namespace ormxx::internal {

class InjectUtility {
public:
    template <typename T>
    std::tuple<std::vector<std::string>, std::vector<std::string>> GetFieldNameAndValue(T* t) {
        std::vector<std::string> field_name_vector;
        std::vector<std::string> field_value_vector;

        auto options = internal::StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitForEach().Build();
        internal::InjectEntrance::StructSchemaEntrance(
                t, options, [&field_name_vector, &field_value_vector](auto&& field, auto&& options) {
                    field_name_vector.push_back(options.field_name);
                    field_value_vector.push_back(internal::FieldToString(field));
                });

        return std::make_tuple(field_name_vector, field_value_vector);
    }
};

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_INJECT_UTILITY_H
