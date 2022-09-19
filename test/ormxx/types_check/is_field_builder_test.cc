#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "fmt/core.h"

#include "ormxx/ormxx.h"

#include "../get_orm.h"

#include "../model/user.h"

using namespace ormxx;
using namespace ormxx::test;

class IsFieldBuilderTest : public testing::Test {
protected:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(IsFieldBuilderTest, is_field_builder) {
    auto* orm = GetORMXX();
    ASSERT_FALSE(orm == nullptr);

    { EXPECT_FALSE(internal::is_field_builder_v<int>); }

    {
        auto res = internal::is_field_builder_v<int, bool>;
        EXPECT_FALSE(res);
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();
        auto u = q.NewFields();

        EXPECT_TRUE(internal::is_field_builder_v<decltype(u.Age.Eq(12))>);
        EXPECT_TRUE(internal::is_field_builder_v<decltype(u.Age.Add(999), u.Name.Value("name"))>);
    }
}
