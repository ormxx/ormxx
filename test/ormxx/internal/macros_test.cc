#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <string>

#include "ormxx/internal/macros.h"

class MacrosTest : public testing::Test {
protected:
    virtual void SetUp() override {}

    virtual void TearDown() override {}
};

#define MACROS_TEST_STR(x) #x

TEST_F(MacrosTest, GetOriginStructName) {
    EXPECT_EQ("", ::ormxx::internal::GetOriginStructName(""));

    EXPECT_EQ(std::string("Test"), ::ormxx::internal::GetOriginStructName(MACROS_TEST_STR(testing::Test)));
    EXPECT_EQ(std::string("MacrosTest"), ::ormxx::internal::GetOriginStructName(MACROS_TEST_STR(MacrosTest)));
}
