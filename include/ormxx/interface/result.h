#ifndef ORMXX_INTERNAL_RESULT_H
#define ORMXX_INTERNAL_RESULT_H

#include "result/result.h"
#include "result/result_or.h"

namespace ormxx {

enum class ErrorCode {
    OK = 0,
    ConnectionError,
    SchemaDeclareError,
    GenerateSQLError,
    ExecuteError,
    OtherError,
};

inline auto ErrorCodeToStr(ErrorCode error_code) {
    static const std::map<ErrorCode, std::string> ErrorCodeToStrMap = {
            {ErrorCode::OK, "OK"},
            {ErrorCode::ConnectionError, "ConnectionError"},
            {ErrorCode::SchemaDeclareError, "SchemaDeclareError"},
            {ErrorCode::GenerateSQLError, "GenerateSQLError"},
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
