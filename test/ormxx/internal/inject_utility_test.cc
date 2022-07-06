#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <string>

#include "ormxx/internal/inject_utility.h"

#include "../model/user.h"

using namespace ormxx;
using namespace ormxx::internal;
using namespace ormxx::test;

class InjectUtilityTest : public testing::Test {
protected:
    virtual void SetUp() override {}

    virtual void TearDown() override {}
};

TEST_F(InjectUtilityTest, GetPrimaryKeyFieldName) {
    {
        auto res = InjectUtility::GetPrimaryKeyFieldName<model::User>();
        EXPECT_TRUE(res.IsOK());
        auto field_name = res.Value();
        EXPECT_EQ(field_name, std::string("ID"));
    }
}
