#ifndef ORMXX_TYPE_TRAITS_CLASS_MEMBER_POINTER_CLASS_H
#define ORMXX_TYPE_TRAITS_CLASS_MEMBER_POINTER_CLASS_H

// https://stackoverflow.com/a/25229199/17040126

namespace ormxx::internal {

template <typename T>
struct class_member_pointer_class;

template <typename Class, typename Value>
struct class_member_pointer_class<Value Class::*> {
    typedef Class type;
};

template <typename T>
using class_member_pointer_class_t = typename class_member_pointer_class<T>::type;

template <typename T>
struct class_member_pointer_value;

template <typename Class, typename Value>
struct class_member_pointer_value<Value Class::*> {
    typedef Value type;
};

template <typename T>
using class_member_pointer_value_t = typename class_member_pointer_value<T>::type;

}  // namespace ormxx::internal

#endif  // ORMXX_TYPE_TRAITS_CLASS_MEMBER_POINTER_CLASS_H
