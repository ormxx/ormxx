#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "fmt/core.h"

#include "ormxx/adaptor/mysql/mysql_adaptor.h"
#include "ormxx/ormxx.h"

#include "./get_orm.h"
#include "./model/user.h"

using namespace ormxx;
using namespace ormxx::test;
using namespace ormxx::adaptor::mysql;

class ORMXXTest : public testing::Test {
protected:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(ORMXXTest, drop_table_test) {
    auto* orm = GetORMXX();

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}
