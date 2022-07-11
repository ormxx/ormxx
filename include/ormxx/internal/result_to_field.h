#ifndef ORMXX_RESULT_TO_FIELD_H
#define ORMXX_RESULT_TO_FIELD_H

#include <optional>
#include "fmt/core.h"

#include "../interface/execute_result.h"
#include "../interface/result.h"
#include "../options/field_type.h"
#include "../types_check/common.h"
#include "result/macros.h"

namespace ormxx::internal {

template <typename T, std::enable_if_t<std::is_same_v<bool, T>, bool> = true, typename O>
Result ResultToField(ExecuteResult& execute_result, bool& field, O&& options) {
    if (options.field_type.cxx_field_type != CXXFieldType::BOOLEAN) {
        RESULT_DIRECT_RETURN(Result::Builder(Result::ErrorCode::GetColumnValueError)
                                     .WithErrorMessage(fmt::format("{} is not a boolean type", options.field_name))
                                     .Build());
    }

    RESULT_VALUE_OR_RETURN(field, execute_result.GetBoolean(options.field_name));
    RESULT_DIRECT_RETURN(Result::OK());
}

template <typename T, std::enable_if_t<std::is_same_v<int32_t, T> || std::is_same_v<int, T>, bool> = true, typename O>
Result ResultToField(ExecuteResult& execute_result, T& field, O&& options) {
    if (options.field_type.cxx_field_type != CXXFieldType::INT) {
        RESULT_DIRECT_RETURN(Result::Builder(Result::ErrorCode::GetColumnValueError)
                                     .WithErrorMessage(fmt::format("{} is not a int32_t type", options.field_name))
                                     .Build());
    }

    RESULT_VALUE_OR_RETURN(field, execute_result.GetInt(options.field_name));
    RESULT_DIRECT_RETURN(Result::OK());
}

template <typename T,
          std::enable_if_t<std::is_same_v<uint32_t, T> || std::is_same_v<unsigned int, T>, bool> = true,
          typename O>
Result ResultToField(ExecuteResult& execute_result, T& field, O&& options) {
    if (options.field_type.cxx_field_type != CXXFieldType::UINT) {
        RESULT_DIRECT_RETURN(Result::Builder(Result::ErrorCode::GetColumnValueError)
                                     .WithErrorMessage(fmt::format("{} is not a uint32_t type", options.field_name))
                                     .Build());
    }

    RESULT_VALUE_OR_RETURN(field, execute_result.GetUInt(options.field_name));
    RESULT_DIRECT_RETURN(Result::OK());
}

template <typename T,
          std::enable_if_t<std::is_same_v<int64_t, T> || std::is_same_v<long long, T>, bool> = true,
          typename O>
Result ResultToField(ExecuteResult& execute_result, T& field, O&& options) {
    if (options.field_type.cxx_field_type != CXXFieldType::INT64) {
        RESULT_DIRECT_RETURN(Result::Builder(Result::ErrorCode::GetColumnValueError)
                                     .WithErrorMessage(fmt::format("{} is not a int64_t type", options.field_name))
                                     .Build());
    }

    RESULT_VALUE_OR_RETURN(field, execute_result.GetInt64(options.field_name));
    RESULT_DIRECT_RETURN(Result::OK());
}

template <typename T,
          std::enable_if_t<std::is_same_v<uint64_t, T> || std::is_same_v<unsigned long long, T>, bool> = true,
          typename O>
Result ResultToField(ExecuteResult& execute_result, T& field, O&& options) {
    if (options.field_type.cxx_field_type != CXXFieldType::UINT64) {
        RESULT_DIRECT_RETURN(Result::Builder(Result::ErrorCode::GetColumnValueError)
                                     .WithErrorMessage(fmt::format("{} is not a uint64_t type", options.field_name))
                                     .Build());
    }

    RESULT_VALUE_OR_RETURN(field, execute_result.GetUInt64(options.field_name));
    RESULT_DIRECT_RETURN(Result::OK());
}

template <typename T, std::enable_if_t<std::is_same_v<double, T>, bool> = true, typename O>
Result ResultToField(ExecuteResult& execute_result, T& field, O&& options) {
    if (options.field_type.cxx_field_type != CXXFieldType::DOUBLE) {
        RESULT_DIRECT_RETURN(Result::Builder(Result::ErrorCode::GetColumnValueError)
                                     .WithErrorMessage(fmt::format("{} is not a double type", options.field_name))
                                     .Build());
    }

    RESULT_VALUE_OR_RETURN(field, execute_result.GetDouble(options.field_name));
    RESULT_DIRECT_RETURN(Result::OK());
}

template <typename T, std::enable_if_t<std::is_same_v<std::string, T>, bool> = true, typename O>
Result ResultToField(ExecuteResult& execute_result, T& field, O&& options) {
    if (options.field_type.cxx_field_type != CXXFieldType::STRING) {
        RESULT_DIRECT_RETURN(Result::Builder(Result::ErrorCode::GetColumnValueError)
                                     .WithErrorMessage(fmt::format("{} is not a string type", options.field_name))
                                     .Build());
    }

    RESULT_VALUE_OR_RETURN(field, execute_result.GetString(options.field_name));
    RESULT_DIRECT_RETURN(Result::OK());
}

template <typename T, typename O>
Result ResultToField(ExecuteResult& execute_result, std::optional<T>& field, O&& options) {
    if (execute_result.IsNull(options.field_name)) {
        field = std::nullopt;
        RESULT_DIRECT_RETURN(Result::OK());
    }

    RESULT_DIRECT_RETURN(ResultToField(execute_result, field.value(), options));
}

// template <typename Field, typename O>
// Result ResultToField([[maybe_unused]] ExecuteResult& execute_result,
//                      [[maybe_unused]] Field& field,
//                      [[maybe_unused]] O&& options) {
//     static_assert(false_v<Field>, "Field type is not supported");
//     RESULT_DIRECT_RETURN(Result::OK());
// }

}  // namespace ormxx::internal

#endif  // ORMXX_RESULT_TO_FIELD_H
