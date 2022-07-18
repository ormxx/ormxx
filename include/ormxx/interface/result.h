#ifndef ORMXX_INTERNAL_RESULT_H
#define ORMXX_INTERNAL_RESULT_H

#include "result/result.h"     // IWYU pragma: export
#include "result/result_or.h"  // IWYU pragma: export

namespace ormxx {

enum class ErrorCode {
    OK = 0,
    NestedError,
    ConnectionError,
    SchemaDeclareError,
    GenerateSQLError,
    NoInvalidPrimaryKeyError,
    GetColumnValueError,
    ExecuteError,
    OtherError,
};

inline auto ErrorCodeToStr(ErrorCode error_code) {
    static const std::map<ErrorCode, std::string> ErrorCodeToStrMap = {
            {ErrorCode::OK, "OK"},
            {ErrorCode::NestedError, "NestedError"},
            {ErrorCode::ConnectionError, "ConnectionError"},
            {ErrorCode::SchemaDeclareError, "SchemaDeclareError"},
            {ErrorCode::GenerateSQLError, "GenerateSQLError"},
            {ErrorCode::NoInvalidPrimaryKeyError, "NoInvalidPrimaryKeyError"},
            {ErrorCode::GetColumnValueError, "GetColumnValueError"},
            {ErrorCode::ExecuteError, "ExecuteError"},
            {ErrorCode::OtherError, "OtherError"},
    };

    if (ErrorCodeToStrMap.count(error_code) == 0) {
        return ErrorCodeToStrMap.rbegin()->second;
    }

    return ErrorCodeToStrMap.at(error_code);
}

using Result = result::Result<ErrorCode>;

template <typename T>
using ResultOr = result::ResultOr<Result, T>;

}  // namespace ormxx

#endif  // ORMXX_INTERNAL_RESULT_H
