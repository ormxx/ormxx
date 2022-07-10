#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <type_traits>

#include "fmt/core.h"

#include "ormxx/type_traits/class_member_pointer.h"

using namespace ormxx;
using namespace ormxx::internal;

class TypeTraitsTest : public testing::Test {
protected:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(TypeTraitsTest, class_member_pointer_test) {
    struct Bar {
        int var;
    };

    EXPECT_TRUE(std::is_same_v<Bar, class_member_pointer_class_t<&Bar::var>>);
    EXPECT_TRUE(std::is_same_v<int, class_member_pointer_value_t<&Bar::var>>);
}
