#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "ormxx/ormxx.h"

using namespace ormxx;

class SQLStatementTest : public testing::Test {
protected:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(SQLStatementTest, AppendString) {
    auto sql_string = SQLStatement();
    sql_string.Append("abc");

    EXPECT_EQ(sql_string.GetSQLString(), "abc");

    sql_string.Append("cba", {SQLStatement::Field()});
    EXPECT_EQ(sql_string.GetSQLString(), "abccba");
    EXPECT_EQ(sql_string.GetFields().size(), 1);
}
