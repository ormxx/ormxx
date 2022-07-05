#ifndef ORMXX_INTERNAL_OVERLOAD_H
#define ORMXX_INTERNAL_OVERLOAD_H

namespace ormxx::internal {

template <class... Fs>
struct overload_set;

template <class F1, class... Fs>
struct overload_set<F1, Fs...> : F1, overload_set<Fs...>::type {
    typedef overload_set type;

    overload_set(F1 head, Fs... tail) : F1(head), overload_set<Fs...>::type(tail...) {}

    using F1::operator();
    using overload_set<Fs...>::type::operator();
};

template <class F>
struct overload_set<F> : F {
    typedef F type;
    using F::operator();
};

template <class... Fs>
typename internal::overload_set<Fs...>::type Overload(Fs... x) {
    return internal::overload_set<Fs...>(x...);
}

}  // namespace ormxx::internal

#endif  // ORMXX_INTERNAL_OVERLOAD_H
