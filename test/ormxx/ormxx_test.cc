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

class ORMXXTest : public testing::Test {
protected:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(ORMXXTest, check_schema_test) {
    auto* orm = GetORMXX();

    {
        auto res = orm->CheckSchema<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->CheckSchema<model::UserErrorSchema>();
        EXPECT_FALSE(res.IsOK());
        auto err_msg = res.Message();
        EXPECT_EQ(err_msg, std::string("field name not found. [field name: `ID2`]"));
    }
}

TEST_F(ORMXXTest, drop_table_test) {
    auto* orm = GetORMXX();

    {
        auto sql_res = GenerateDropTableSQL<model::User>();
        EXPECT_TRUE(sql_res.IsOK());
        auto sql = sql_res.Value();
        EXPECT_EQ(sql, std::string("DROP TABLE IF EXISTS `user`;"));
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, create_table_test) {
    auto* orm = GetORMXX();

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto sql_res = GenerateCreateTableSQL<model::User>();
        EXPECT_TRUE(sql_res.IsOK());
        auto sql = sql_res.Value();
        EXPECT_EQ(sql, std::string(R"(
CREATE TABLE `user` (
    `id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'id',
    `name` VARCHAR(255) NOT NULL DEFAULT '' COMMENT 'name',
    `age` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT 'age',
    PRIMARY KEY (`id`) USING BTREE,
    INDEX `idx_name_age` (`name`, `age`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COMMENT = 'User';
)"));
    }

    {
        auto res = orm->CreateTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, insert_test) {
    auto* orm = GetORMXX();

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->CreateTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto user = model::User().SetName("test").SetAge(1);

        auto sql_res = GenerateInsertSQL(&user);
        EXPECT_TRUE(sql_res.IsOK());
        auto sql = sql_res.Value();
        EXPECT_EQ(sql, std::string(R"(INSERT INTO `user` (`name`, `age`) VALUES ('test', 1);)"));

        auto res = orm->Insert(&user);
        EXPECT_TRUE(res.IsOK());

        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        const auto user = model::User().SetName("test").SetAge(2);

        auto sql_res = GenerateInsertSQL(&user);
        EXPECT_TRUE(sql_res.IsOK());
        auto sql = sql_res.Value();
        EXPECT_EQ(sql, std::string(R"(INSERT INTO `user` (`name`, `age`) VALUES ('test', 2);)"));

        auto res = orm->Insert(&user);
        EXPECT_TRUE(res.IsOK());

        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        auto res = orm->Insert<model::User>(model::User().SetName("name1").SetAge(3));
        EXPECT_TRUE(res.IsOK());

        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        std::vector<model::User> user_vector;
        for (int i = 4; i <= 10; i++) {
            user_vector.push_back(model::User().SetName(fmt::format("name{}", i)).SetAge(i));
        }

        auto sql_res = GenerateInsertSQL(&user_vector);
        EXPECT_TRUE(sql_res.IsOK());
        auto sql = sql_res.Value();
        EXPECT_EQ(sql, std::string(R"(INSERT INTO `user` (`name`, `age`) VALUES
 ('name4', 4),
 ('name5', 5),
 ('name6', 6),
 ('name7', 7),
 ('name8', 8),
 ('name9', 9),
 ('name10', 10);
)"));

        auto res = orm->Insert(user_vector);
        EXPECT_TRUE(res.IsOK());

        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 7);
    }

    {
        auto user = model::User().SetID(999).SetName("dd").SetAge(10);

        auto sql_res = GenerateInsertSQL(&user);
        EXPECT_TRUE(sql_res.IsOK());
        auto sql = sql_res.Value();
        EXPECT_EQ(sql, std::string(R"(INSERT INTO `user` (`id`, `name`, `age`) VALUES (999, 'dd', 10);)"));

        auto res = orm->Insert(&user);
        EXPECT_TRUE(res.IsOK());

        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, delete_test) {
    auto* orm = GetORMXX();

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->CreateTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto user = model::User().SetID(1).SetName("test").SetAge(1);
        auto insert_res = orm->Insert(user);
        EXPECT_TRUE(insert_res.IsOK());

        auto sql_res = GenerateDeleteSQL(&user);
        EXPECT_TRUE(sql_res.IsOK());
        auto sql = sql_res.Value();
        EXPECT_EQ(sql, std::string("DELETE FROM `user` WHERE `id` = 1;"));

        auto res = orm->Delete<model::User>(&user);
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, update_test) {
    auto* orm = GetORMXX();

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->CreateTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto user = model::User().SetID(1).SetName("test").SetAge(1);
        auto insert_res = orm->Insert(&user);
        EXPECT_TRUE(insert_res.IsOK());

        {
            user.SetName("test2");

            auto sql_res = GenerateUpdateSQL(&user);
            EXPECT_TRUE(sql_res.IsOK());
            auto sql = sql_res.Value();
            EXPECT_EQ(sql, std::string(R"(UPDATE `user` SET `name` = 'test2' WHERE `id` = 1;)"));

            auto res = orm->Update(&user);
            EXPECT_TRUE(res.IsOK());
        }

        {
            user.SetName("test3");

            auto sql_res = GenerateUpdateSQL(&user);
            EXPECT_TRUE(sql_res.IsOK());
            auto sql = sql_res.Value();
            EXPECT_EQ(sql, std::string(R"(UPDATE `user` SET `name` = 'test3' WHERE `id` = 1;)"));

            auto res = orm->Update(&user);
            EXPECT_TRUE(res.IsOK());
        }
    }
}
