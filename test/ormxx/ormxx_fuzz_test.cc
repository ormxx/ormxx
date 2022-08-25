#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "fmt/core.h"

#include "ormxx/adaptor/mysql/mysql_adaptor.h"
#include "ormxx/ormxx.h"

#include "./get_orm.h"

#include "./model/user.error_schema.h"
#include "./model/user.h"

using namespace ormxx;
using namespace ormxx::test;
using namespace ormxx::adaptor::mysql;

class ORMXXFuzzTest : public testing::Test {
protected:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(ORMXXFuzzTest, fuzz_test) {
    auto* orm = GetORMXX();
    EXPECT_FALSE(orm == nullptr);

    {
        auto res = std::invoke([&]() -> Result {
            RESULT_VALUE_OR_RETURN(auto* conn, orm->getWriteConnection());
            conn->Close();
            EXPECT_TRUE(conn->IsClosed());
            orm->releaseConnection(conn);

            RESULT_VALUE_OR_RETURN(conn, orm->getWriteConnection());
            EXPECT_FALSE(conn->IsClosed());

            auto res = conn->ExecuteQuery("SELECT 1;");
            EXPECT_TRUE(res.IsOK());

            return Result::OK();
        });

        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXFuzzTest, escape_characters) {
    auto* orm = GetORMXX();
    EXPECT_FALSE(orm == nullptr);

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->CreateTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto user = model::User().SetName(R"(
{
        "main": "659733",
        "t": "{\"e\":\"3-71\",\"c\":\"s:5\",\"i\":\"60\"}"
}
        )");

        SNAPSHOT(user.GetName());

        auto res = orm->Insert(&user);
        EXPECT_TRUE(res.IsOK());

        auto sql = orm->getLastSQLString();
        SNAPSHOT(sql);
    }

    {
        auto res = orm->NewQueryBuilder<model::User>().First();
        EXPECT_TRUE(res.IsOK());
        auto user = std::move(res.Value());
        SNAPSHOT(user.GetName());
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}
