#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <string>

#include "ormxx/internal/utils.h"

using namespace ormxx;
using namespace ormxx::internal;

class MacrosTest : public testing::Test {
protected:
    virtual void SetUp() override {}

    virtual void TearDown() override {}
};

#define MACROS_TEST_STR(x) #x

TEST_F(MacrosTest, GetOriginStructName) {
    EXPECT_EQ("", Utils::GetOriginStructName(""));

    EXPECT_EQ(std::string("Test"), Utils::GetOriginStructName(MACROS_TEST_STR(testing::Test)));
    EXPECT_EQ(std::string("MacrosTest"), Utils::GetOriginStructName(MACROS_TEST_STR(MacrosTest)));
}
