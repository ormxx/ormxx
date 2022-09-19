#ifndef ORMXX_INTERNAL_RESULT_TO_ENTITY_H
#define ORMXX_INTERNAL_RESULT_TO_ENTITY_H

#include <type_traits>
#include <vector>

#include "../interface/execute_result.h"
#include "../interface/result.h"
#include "../internal/inject_entrance.h"
#include "../internal/inject_utility.h"
#include "../internal/struct_schema_entrance_options.h"
#include "../options/field_type.h"
#include "../types_check/has_ormxx_inject.h"
#include "./result_to_field.h"

namespace ormxx::internal {

template <typename T, std::enable_if_t<has_ormxx_inject_v<T>, bool> = true>
inline Result ResultToEntity(ExecuteResult& execute_result, T& t) {
    if (execute_result.RowsCount() < 1) {
        RESULT_DIRECT_RETURN(Result::Builder(Result::ErrorCode::ExecuteError)
                                     .WithErrorMessage(fmt::format("No data found"))
                                     .Build());
    }

    execute_result.Next();

    auto res = Result::OK();

    auto options = StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitForEach().Build();
    InjectEntrance::StructSchemaEntrance(&t, options, [&execute_result, &res](auto&& field, auto&& options) {
        if (!res.IsOK()) {
            return;
        }

        res = ResultToField(execute_result, *field, options);
    });

    RESULT_DIRECT_RETURN(res);
}

template <typename T, std::enable_if_t<has_ormxx_inject_v<T>, bool> = true>
inline Result ResultToEntity(ExecuteResult& execute_result, std::vector<T>& t_vec) {
    while (execute_result.Next()) {
        auto res = Result::OK();

        T t;

        auto options = StructSchemaEntranceOptionsBuilder().WithVisitField().WithVisitForEach().Build();
        InjectEntrance::StructSchemaEntrance(&t, options, [&execute_result, &res](auto&& field, auto&& options) {
            if (!res.IsOK()) {
                return;
            }

            res = ResultToField(execute_result, *field, options);
        });

        if (!res.IsOK()) {
            RESULT_DIRECT_RETURN(res);
        }

        t_vec.push_back(t);
    }

    return Result::OK();
}

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_RESULT_TO_ENTITY_H
