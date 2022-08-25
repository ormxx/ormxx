#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "ormxx/ormxx.h"

using namespace ormxx;

class SQLStringTest : public testing::Test {
protected:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(SQLStringTest, AppendString) {
    auto sql_string = SQLString();
    sql_string.Append("abc");

    EXPECT_EQ(sql_string.GetSQLString(), "abc");

    sql_string.Append("cba", {SQLString::Field()});
    EXPECT_EQ(sql_string.GetSQLString(), "abccba");
    EXPECT_EQ(sql_string.GetFields().size(), 1);
}
