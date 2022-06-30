#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include "fmt/core.h"

#include "ormxx/adaptor/mysql/mysql_connection_config.h"
#include "ormxx/adaptor/mysql/mysql_connection_pool.h"
#include "ormxx/adaptor/mysql/mysql_helper.h"
#include "ormxx/adaptor/mysql/mysql_result.h"

using namespace ormxx::adaptor::mysql;

std::unique_ptr<MySQLConnectionPool> connection_pool = nullptr;

constexpr std::string_view kTableName = "mysqlclient_unittest_table_FE041CA5_D3C1_4758_83A3_28550E3AB66B";

class MySQLClientTest : public testing::Test {
protected:
    virtual void SetUp() override {
        connection_pool.reset(MySQLConnectionPool::Builder().BuildPtr());

        auto* hostname = std::getenv("MYSQL_HOSTNAME");
        auto* port = std::getenv("MYSQL_PORT");
        auto* username = std::getenv("MYSQL_USERNAME");
        auto* password = std::getenv("MYSQL_PASSWORD");
        auto* schema = std::getenv("MYSQL_SCHEMA");

        ASSERT_NE(hostname, nullptr);
        ASSERT_NE(username, nullptr);
        ASSERT_NE(password, nullptr);
        ASSERT_NE(schema, nullptr);

        auto config = MySQLConnectionConfig::Builder()
                              .WithHostname(hostname)
                              .WithPort(port ? std::stoi(port) : 3306)
                              .WithUsername(username)
                              .WithPassword(password)
                              .WithSchema(schema)
                              .Build();

        connection_pool->AddConfig(config);
    }

    virtual void TearDown() override {}
};

TEST_F(MySQLClientTest, mysqlclient_test) {
    auto helper = connection_pool->GetConnectionHelper();
    EXPECT_NE(helper.GetConnection(), nullptr);

    {
        auto res = helper.Execute(fmt::format("DROP TABLE IF EXISTS `{}`;", kTableName));
        EXPECT_TRUE(res.HasResult());
    }

    {
        auto res = helper.Execute(fmt::format(R"(
CREATE TABLE {}  (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'incr id',
  `main_call_uuid` varchar(64) NOT NULL COMMENT 'main call uuid',
  `event_body` MEDIUMTEXT NOT NULL COMMENT 'event body',
  `created_time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'created time',
  `update_time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'update time',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_created_time` (`created_time`),
  INDEX `idx_update_time` (`update_time`),
  INDEX `uniq_call_uuid` (`main_call_uuid`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4  COMMENT = 'mysqlclient test table';
)",
                kTableName));
        EXPECT_TRUE(res.HasResult());
    }

    {
        auto res = helper.ExecuteUpdate(fmt::format(R"(
INSERT INTO {} (`main_call_uuid`, `event_body`) VALUES ('176BED2B-1AB3-47C1-AF25-FA29313A5FF_1', '1');
        )",
                kTableName));
        EXPECT_TRUE(res.HasResult());
        EXPECT_EQ(res.UpdatedRows(), 1);
    }

    {
        auto res = helper.ExecuteUpdate(fmt::format(R"(
INSERT INTO {} (`main_call_uuid`, `event_body`) VALUES ('176BED2B-1AB3-47C1-AF25-FA29313A5FF_2', '2');
        )",
                kTableName));
        EXPECT_TRUE(res.HasResult());
        EXPECT_EQ(res.UpdatedRows(), 1);
    }

    {
        auto res = helper.ExecuteUpdate(fmt::format(R"(
INSERT INTO {} (`main_call_uuid`, `event_body`) VALUES ('176BED2B-1AB3-47C1-AF25-FA29313A5FF_3', '3');
        )",
                kTableName));
        EXPECT_TRUE(res.HasResult());
        EXPECT_EQ(res.UpdatedRows(), 1);
    }

    {
        auto res = helper.ExecuteQuery(fmt::format(R"(
SELECT * FROM {};
        )",
                kTableName));
        EXPECT_TRUE(res.HasResult());
        EXPECT_EQ(res.RowsCount(), 3);

        for (int i = 0; i < res.UpdatedRows(); i++) {
            res.Next();
            std::string main_call_uuid = "";
            std::string event_body = "";
            res.AssignColumnToVar(main_call_uuid, "main_call_uuid");
            res.AssignColumnToVar(event_body, "event_body");

            EXPECT_EQ(main_call_uuid, fmt::format("176BED2B-1AB3-47C1-AF25-FA29313A5FF_{}", i + 1));
            EXPECT_EQ(event_body, fmt::format("{}", i + 1));
        }
    }

    {
        auto res = helper.ExecuteUpdate(fmt::format(R"(
UPDATE {}
SET `event_body` = '4';
        )",
                kTableName));
        EXPECT_TRUE(res.HasResult());
        EXPECT_EQ(res.UpdatedRows(), 3);
    }

    {
        auto res = helper.Execute(fmt::format("DROP TABLE IF EXISTS `{}`;", kTableName));
        EXPECT_TRUE(res.HasResult());
    }
}
