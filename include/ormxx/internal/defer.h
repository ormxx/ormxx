#ifndef ORMXX_INTERNAL_DEFER_H
#define ORMXX_INTERNAL_DEFER_H

#include <functional>

#include "./macros_utility.h"

namespace ormxx::internal {

class Defer {
public:
    Defer() = default;

    Defer(const Defer&) = delete;
    void operator=(const Defer&) = delete;

    Defer(Defer&&) = delete;
    Defer& operator=(Defer&&) = delete;

    template <typename F, typename... Args>
    Defer(F&& func, Args&&... args) {
        auto f = std::function<void()>(std::bind(std::forward<F>(func), std::forward<Args>(args)...));
        func_.swap(f);
    }

    template <typename F, typename... Args>
    void Reset(F&& func, Args&&... args) {
        auto f = std::function<void()>(std::bind(std::forward<F>(func), std::forward<Args>(args)...));
        func_.swap(f);
    }

    void Cancel() {
        std::function<void()> tmp;
        tmp.swap(func_);
    }

    ~Defer() {
        if (func_) {
            func_();
        }
    }

private:
    std::function<void()> func_;
};

#define __ORMXX_INTERNAL_DEFER_NAME __ORMXX_CONCAT(__ORMXX_INTERNAL_DEFER_INLINE_, __LINE__)

#define __ORMXX_DEFER(...) ::ormxx::internal::Defer __ORMXX_INTERNAL_DEFER_NAME(__VA_ARGS__)

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_DEFER_H
