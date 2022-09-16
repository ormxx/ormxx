#ifndef ORMXX_INTERNAL_INJECT_UTILITY_H
#define ORMXX_INTERNAL_INJECT_UTILITY_H

#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <vector>

#include "../interface/result.h"
#include "../options/key_options.h"
#include "../types_check/has_ormxx_inject.h"
#include "./field_to_string.h"
#include "./inject_entrance.h"
#include "./query_fields_builder.h"
#include "./struct_schema_entrance_options.h"

namespace ormxx::internal {

class InjectUtility {
public:
    template <typename T, std::enable_if_t<has_ormxx_inject_v<T>, bool> = true>
    static std::vector<std::string> GetAllFieldName(T* t) {
        std::vector<std::string> field_name_vector;

        auto options = internal::StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitForEach().Build();
        internal::InjectEntrance::StructSchemaEntrance(
                t, options, [&field_name_vector]([[maybe_unused]] auto&& field, auto&& options) {
                    field_name_vector.push_back(options.field_name);
                });

        return field_name_vector;
    }

    template <typename T, std::enable_if_t<has_ormxx_inject_v<T>, bool> = true>
    static std::tuple<std::vector<std::string>, std::vector<std::string>> GetFieldNameAndValue(T* t) {
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

    template <typename T, std::enable_if_t<has_ormxx_inject_v<T>, bool> = true>
    static ResultOr<std::string> GetPrimaryKeyFieldName() {
        int ix = 0;

        std::vector<std::string> field_name_vector;

        auto options = internal::StructSchemaEntranceOptionsBuilder()
                               .WithVisitKey()
                               .WithVisitKeyByKeyType(KeyOptions::KeyType::PRIMARY)
                               .Build();
        internal::InjectEntrance::StructSchemaEntrance<T>(nullptr, options, [&ix, &field_name_vector](auto&& options) {
            ++ix;
            if (ix > 1) {
                return;
            }

            field_name_vector = options.field_name;
        });

        if (ix == 0) {
            return Result::Builder(Result::ErrorCode::NoInvalidPrimaryKeyError)
                    .WithErrorMessage("No primary key found")
                    .Build();
        } else if (ix > 1) {
            return Result::Builder(Result::ErrorCode::NoInvalidPrimaryKeyError)
                    .WithErrorMessage("Multiple primary key found")
                    .Build();
        } else if (field_name_vector.size() != 1) {
            return Result::Builder(Result::ErrorCode::NoInvalidPrimaryKeyError)
                    .WithErrorMessage("Multiple primary key column found")
                    .Build();
        }

        auto field_name = field_name_vector.front();
        return field_name;
    }

    template <typename T, typename FieldType>
    static auto GetQueryFieldBuilder(const std::string& origin_field_name) {
        T t{};

        QueryFieldsBuilder<FieldType> query_fields_builder{};

        auto options = internal::StructSchemaEntranceOptionsBuilder()
                               .WithVisitField()
                               .WithVisitFieldByName(origin_field_name)
                               .Build();
        internal::InjectEntrance::StructSchemaEntrance(
                &t, options, [&query_fields_builder]([[maybe_unused]] auto&& field, auto&& options) {
                    query_fields_builder.origin_field_name = options.origin_field_name;
                    query_fields_builder.field_name = options.field_name;
                    query_fields_builder.field_type = options.field_type;
                });

        query_fields_builder.init();

        return query_fields_builder;
    }

    template <typename T, std::enable_if_t<has_ormxx_inject_v<T> && !std::is_const_v<T>, bool> = true>
    static void ClearIsSetMap(T* t) {
        InjectEntrance::GetIsSetMap(t).clear();
    }
};

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_INJECT_UTILITY_H
