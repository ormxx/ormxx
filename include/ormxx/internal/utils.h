#ifndef ORMXX_INTERNAL_UTILS_H
#define ORMXX_INTERNAL_UTILS_H

#include <algorithm>
#include <string>

namespace ormxx::internal {

class Utils {
public:
    static std::string GetOriginStructName(const std::string& origin_struct_name) {
        std::string res = "";

        for (int i = (int)origin_struct_name.size() - 1; i >= 0; i--) {
            if (origin_struct_name[i] == ':') {
                break;
            }

            res += origin_struct_name[i];
        }

        std::reverse(res.begin(), res.end());

        return res;
    }
};

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_UTILS_H
