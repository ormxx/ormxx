#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "fmt/core.h"

#include "ormxx/adaptor/mysql/mysql_adaptor.h"
#include "ormxx/ormxx.h"

#include "../../get_orm.h"

using namespace ormxx;
using namespace ormxx::test;
using namespace ormxx::adaptor::mysql;

constexpr std::string_view kTableName = "mysqlclient_unittest_table_FE041CA5_D3C1_4758_83A3_28550E3AB66B";

class MySQLClientTest : public testing::Test {
protected:
    virtual void SetUp() override {}

    virtual void TearDown() override {}
};

TEST_F(MySQLClientTest, mysqlclient_test) {
    auto* orm = GetORMXX();

    {
        auto res = orm->Execute(fmt::format("DROP TABLE IF EXISTS `{}`;", kTableName));
        EXPECT_TRUE(res.IsOK());
        auto execute_res = std::move(res.Value());
    }

    {
        auto res = orm->Execute(fmt::format(
                R"(
CREATE TABLE {}  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'incr id',
  `main_uuid` varchar(64) NOT NULL COMMENT 'main uuid',
  `event_body` MEDIUMTEXT NOT NULL COMMENT 'event body',
  `created_time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'created time',
  `update_time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'update time',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_created_time` (`created_time`),
  INDEX `idx_update_time` (`update_time`),
  INDEX `uniq_main_uuid` (`main_uuid`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4  COMMENT = 'mysqlclient test table';
)",
                kTableName));
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->ExecuteUpdate(fmt::format(
                R"(
INSERT INTO {} (`main_uuid`, `event_body`) VALUES ('176BED2B-1AB3-47C1-AF25-FA29313A5FF_1', '1');
        )",
                kTableName));
        EXPECT_TRUE(res.IsOK());
        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        auto res = orm->ExecuteUpdate(fmt::format(
                R"(
INSERT INTO {} (`main_uuid`, `event_body`) VALUES ('176BED2B-1AB3-47C1-AF25-FA29313A5FF_2', '2');
        )",
                kTableName));
        EXPECT_TRUE(res.IsOK());
        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        auto res = orm->ExecuteUpdate(fmt::format(
                R"(
INSERT INTO {} (`main_uuid`, `event_body`) VALUES ('176BED2B-1AB3-47C1-AF25-FA29313A5FF_3', '3');
        )",
                kTableName));
        EXPECT_TRUE(res.IsOK());
        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        auto res = orm->ExecuteQuery(fmt::format(
                R"(
    SELECT * FROM {};
            )",
                kTableName));
        EXPECT_TRUE(res.IsOK());
        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsCount(), 3);

        for (int i = 0; i < execute_res->RowsAffected(); i++) {
            execute_res->Next();

            std::string main_uuid = "";
            std::string event_body = "";
            execute_res->AssignColumn(main_uuid, "main_uuid");
            execute_res->AssignColumn(event_body, "event_body");

            EXPECT_EQ(main_uuid, fmt::format("176BED2B-1AB3-47C1-AF25-FA29313A5FF_{}", i + 1));
            EXPECT_EQ(event_body, fmt::format("{}", i + 1));
        }
    }

    {
        auto res = orm->ExecuteUpdate(fmt::format(
                R"(
UPDATE {}
SET `event_body` = '4';
        )",
                kTableName));
        EXPECT_TRUE(res.IsOK());
        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 3);
    }

    {
        auto res = orm->Execute(fmt::format("DROP TABLE IF EXISTS `{}`;", kTableName));
        EXPECT_TRUE(res.IsOK());
    }
}
