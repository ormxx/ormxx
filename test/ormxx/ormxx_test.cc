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
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string("DROP TABLE IF EXISTS `user`;");
        EXPECT_EQ(sql, expected_sql);
    }
}

TEST_F(ORMXXTest, create_table_test) {
    auto* orm = GetORMXX();

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->CreateTable<model::User>();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(
CREATE TABLE `user` (
    `id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'id',
    `name` VARCHAR(255) NOT NULL DEFAULT '' COMMENT 'name',
    `age` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT 'age',
    `update_timestamp` TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) ON UPDATE CURRENT_TIMESTAMP(6) COMMENT 'update_timestamp',
    `insert_timestamp` TIMESTAMP(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) COMMENT 'insert_timestamp',
    PRIMARY KEY (`id`) USING BTREE,
    INDEX `idx_name_age` (`name`, `age`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COMMENT = 'User';
)");
        EXPECT_EQ(sql, expected_sql);

        auto msg = res.Message();
        std::string("OK");
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

        auto res = orm->Insert(&user);
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(INSERT INTO `user` (`name`, `age`) VALUES (?, ?);)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[test, 1]");
        EXPECT_EQ(fields, expected_fields);

        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        const auto user = model::User().SetName("test").SetAge(2);

        auto res = orm->Insert(&user);
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(INSERT INTO `user` (`name`, `age`) VALUES (?, ?);)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[test, 2]");
        EXPECT_EQ(fields, expected_fields);

        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        auto res = orm->Insert<model::User>(model::User().SetName("name1").SetAge(3));
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(INSERT INTO `user` (`name`, `age`) VALUES (?, ?);)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[name1, 3]");
        EXPECT_EQ(fields, expected_fields);

        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 1);
    }

    {
        std::vector<model::User> user_vector;
        for (int i = 4; i <= 10; i++) {
            user_vector.push_back(model::User().SetName(fmt::format("name{}", i)).SetAge(i));
        }

        auto res = orm->Insert(user_vector);
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(INSERT INTO `user` (`name`, `age`) VALUES
 (?, ?),
 (?, ?),
 (?, ?),
 (?, ?),
 (?, ?),
 (?, ?),
 (?, ?);
)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields =
                std::string("[name4, 4, name5, 5, name6, 6, name7, 7, name8, 8, name9, 9, name10, 10]");
        EXPECT_EQ(fields, expected_fields);

        auto execute_res = std::move(res.Value());
        EXPECT_EQ(execute_res->RowsAffected(), 7);
    }

    {
        auto user = model::User().SetID(999).SetName("dd").SetAge(10);

        auto res = orm->Insert(&user);
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(INSERT INTO `user` (`id`, `name`, `age`) VALUES (?, ?, ?);)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[999, dd, 10]");
        EXPECT_EQ(fields, expected_fields);

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

        auto res = orm->Delete<model::User>(&user);
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(DELETE FROM `user` WHERE `id` = ?;)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[1]");
        EXPECT_EQ(fields, expected_fields);
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

            auto res = orm->Update(&user);
            EXPECT_TRUE(res.IsOK());

            const auto& last_sql = orm->getLastSQLStatement();

            const auto& sql = last_sql.GetSQLString();
            const auto expected_sql = std::string(R"(UPDATE `user` SET `name` = ? WHERE `id` = ?;)");
            EXPECT_EQ(sql, expected_sql);

            const auto fields = last_sql.FieldsToString();
            const auto expected_fields = std::string("[test2, 1]");
            EXPECT_EQ(fields, expected_fields);
        }

        {
            user.SetName("test3");

            auto res = orm->Update(&user);
            EXPECT_TRUE(res.IsOK());

            const auto& last_sql = orm->getLastSQLStatement();

            const auto& sql = last_sql.GetSQLString();
            const auto expected_sql = std::string(R"(UPDATE `user` SET `name` = ? WHERE `id` = ?;)");
            EXPECT_EQ(sql, expected_sql);

            const auto fields = last_sql.FieldsToString();
            const auto expected_fields = std::string("[test3, 1]");
            EXPECT_EQ(fields, expected_fields);
        }
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, first_test) {
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
    }

    {
        auto res = orm->First<model::User>();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(
                "SELECT `user`.`id`, `user`.`name`, `user`.`age`, `user`.`update_timestamp`, `user`.`insert_timestamp` FROM `user` LIMIT 1;");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[]");
        EXPECT_EQ(fields, expected_fields);

        auto user = std::move(res.Value());

        EXPECT_EQ(user.GetID(), 1);
        EXPECT_EQ(user.GetName(), "test");
        EXPECT_EQ(user.GetAge(), 1);
    }

    {
        model::User user;
        auto res = orm->First(&user);
        EXPECT_TRUE(res.IsOK());

        EXPECT_EQ(user.GetID(), 1);
        EXPECT_EQ(user.GetName(), "test");
        EXPECT_EQ(user.GetAge(), 1);
    }

    {
        auto res = orm->NewQueryBuilder<model::User>().Where(model::User().SetID(1)).First();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(
                R"(SELECT `user`.`id`, `user`.`name`, `user`.`age`, `user`.`update_timestamp`, `user`.`insert_timestamp` FROM `user` WHERE (`id` = ?) LIMIT 1;)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[1]");
        EXPECT_EQ(fields, expected_fields);

        auto user = res.Value();
        EXPECT_EQ(user.GetID(), 1);
        EXPECT_EQ(user.GetName(), "test");
        EXPECT_EQ(user.GetAge(), 1);
    }

    {
        auto res = orm->NewQueryBuilder<model::User>().Where(model::User().SetID(1).SetName("test")).First();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(
                R"(SELECT `user`.`id`, `user`.`name`, `user`.`age`, `user`.`update_timestamp`, `user`.`insert_timestamp` FROM `user` WHERE (`id` = ? AND `name` = ?) LIMIT 1;)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[1, test]");
        EXPECT_EQ(fields, expected_fields);

        auto user = res.Value();
        EXPECT_EQ(user.GetID(), 1);
        EXPECT_EQ(user.GetName(), "test");
        EXPECT_EQ(user.GetAge(), 1);
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, find_test) {
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
        for (int i = 1; i <= 10; i++) {
            auto user = model::User().SetID(i).SetName("test").SetAge(i);
            auto insert_res = orm->Insert(&user);
            EXPECT_TRUE(insert_res.IsOK());
        }
    }

    {
        auto res = orm->NewQueryBuilder<model::User>().Where(model::User().SetName("test")).Find();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(
                R"(SELECT `user`.`id`, `user`.`name`, `user`.`age`, `user`.`update_timestamp`, `user`.`insert_timestamp` FROM `user` WHERE (`name` = ?);)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[test]");
        EXPECT_EQ(fields, expected_fields);

        auto s_vec = std::move(res.Value());
        EXPECT_EQ(s_vec.size(), 10);

        for (int i = 0; i < 10; i++) {
            EXPECT_EQ(s_vec[i].GetID(), i + 1);
            EXPECT_EQ(s_vec[i].GetName(), "test");
            EXPECT_EQ(s_vec[i].GetAge(), i + 1);
        }
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, transaction_test) {
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
        auto res = orm->Transaction([&]() -> Result {
            auto user = model::User().SetID(1).SetName("test").SetAge(1);
            RESULT_OK_OR_RETURN(orm->Insert(&user));
            user.SetAge(2);
            RESULT_DIRECT_RETURN(orm->Update(&user));
        });

        EXPECT_TRUE(res.IsOK());
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, QueryBuilder_Select) {
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
        for (int i = 1; i <= 20; i++) {
            auto user = model::User().SetID(i).SetName("test").SetAge(i);
            auto insert_res = orm->Insert(&user);
            EXPECT_TRUE(insert_res.IsOK());
        }
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();
        auto u = q.NewFields();

        auto res = q.Where(u.Age.Between(5, 6), u.Name.Eq("test")).Find();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(
                R"(SELECT `user`.`id`, `user`.`name`, `user`.`age`, `user`.`update_timestamp`, `user`.`insert_timestamp` FROM `user` WHERE ((`age` BETWEEN ? AND ?) AND (`name` = ?));)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[5, 6, test]");
        EXPECT_EQ(fields, expected_fields);

        auto s_vec = std::move(res.Value());
        EXPECT_EQ(s_vec.size(), 2);
        EXPECT_EQ(s_vec[0].GetAge(), 5);
        EXPECT_EQ(s_vec[1].GetAge(), 6);
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();
        auto u = q.NewFields();

        auto res = q.Where(u.Age.Between(9, 10)).Order(u.Age.Desc()).Find();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(
                R"(SELECT `user`.`id`, `user`.`name`, `user`.`age`, `user`.`update_timestamp`, `user`.`insert_timestamp` FROM `user` WHERE ((`age` BETWEEN ? AND ?)) ORDER BY `age` DESC;)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[9, 10]");
        EXPECT_EQ(fields, expected_fields);

        auto s_vec = std::move(res.Value());
        EXPECT_EQ(s_vec.size(), 2);
        EXPECT_EQ(s_vec[0].GetAge(), 10);
        EXPECT_EQ(s_vec[1].GetAge(), 9);
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, QueryFieldsBuilder_Select_1) {
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
        for (int i = 1; i <= 20; i++) {
            auto user = model::User().SetID(i).SetName("test").SetAge(i).SetInsertTimestamp(
                    fmt::format("2022-09-{} 11:00:00", i));
            auto insert_res = orm->Insert(&user);
            EXPECT_TRUE(insert_res.IsOK());
        }
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();
        auto u = q.NewFields();

        const std::string name = "test";

        auto res =
                q.Where(u.InsertTimestamp.Between("2022-8-30 10:00:00", "2022-9-5 12:00:00"), u.Name.Eq(name)).Find();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(
                R"(SELECT `user`.`id`, `user`.`name`, `user`.`age`, `user`.`update_timestamp`, `user`.`insert_timestamp` FROM `user` WHERE ((`insert_timestamp` BETWEEN ? AND ?) AND (`name` = ?));)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[2022-8-30 10:00:00, 2022-9-5 12:00:00, test]");
        EXPECT_EQ(fields, expected_fields);

        auto s_vec = std::move(res.Value());
        EXPECT_EQ(s_vec.size(), 5);

        for (int i = 1; i <= 5; i++) {
            EXPECT_EQ(s_vec[i - 1].GetInsertTimestamp(), fmt::format("2022-09-0{} 11:00:00", i));
        }
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, QueryFieldsBuilder_Update) {
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
        for (int i = 1; i <= 20; i++) {
            auto user = model::User().SetID(i).SetName("test").SetAge(i).SetInsertTimestamp(
                    fmt::format("2022-09-{} 11:00:00", i));
            auto insert_res = orm->Insert(&user);
            EXPECT_TRUE(insert_res.IsOK());
        }
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();
        auto u = q.NewFields();

        const std::string name = "test";

        auto res = q.Where(u.InsertTimestamp.Between("2022-8-30 10:00:00", "2022-9-5 12:00:00"), u.Name.Eq(name))
                           .Update(model::User{}.SetAge(999));
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(
                R"(UPDATE `user` SET `age` = ? WHERE ((`insert_timestamp` BETWEEN ? AND ?) AND (`name` = ?));)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[999, 2022-8-30 10:00:00, 2022-9-5 12:00:00, test]");
        EXPECT_EQ(fields, expected_fields);

        {
            auto res = q.Where(u.Age.Eq(999)).Find();
            auto s_vec = std::move(res.Value());
            EXPECT_EQ(s_vec.size(), 5);
        }
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, QueryFieldsBuilder_Update_1) {
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
        for (int i = 1; i <= 20; i++) {
            auto user = model::User().SetID(i).SetName("test").SetAge(i).SetInsertTimestamp(
                    fmt::format("2022-09-{} 11:00:00", i));
            auto insert_res = orm->Insert(&user);
            EXPECT_TRUE(insert_res.IsOK());
        }
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();
        auto u = q.NewFields();

        auto res = q.Where(u.Age.Gte(20)).Update(u.Age.Add(5), u.Name.Value("test2"));
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql =
                std::string(R"(UPDATE `user` SET `age` = `age` + ?, `name` = ? WHERE ((`age` >= ?));)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[5, test2, 20]");
        EXPECT_EQ(fields, expected_fields);

        {
            auto res = q.Where(u.Age.Eq(25)).Find();
            auto s_vec = std::move(res.Value());
            EXPECT_EQ(s_vec.size(), 1);
        }
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, QueryFieldsBuilder_Update_2) {
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
        for (int i = 1; i <= 20; i++) {
            auto user = model::User().SetID(i).SetName("test").SetAge(i).SetInsertTimestamp(
                    fmt::format("2022-09-{} 11:00:00", i));
            auto insert_res = orm->Insert(&user);
            EXPECT_TRUE(insert_res.IsOK());
        }
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();
        auto u = q.NewFields();

        auto res = q.Limit(1).Update(u.Age.Value(99), u.Name.Value("test2"));
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(UPDATE `user` SET `age` = ?, `name` = ? LIMIT 1;)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[99, test2]");
        EXPECT_EQ(fields, expected_fields);

        {
            auto res = q.Where(u.Age.Eq(99)).Find();
            auto s_vec = std::move(res.Value());
            EXPECT_EQ(s_vec.size(), 1);
            EXPECT_EQ(s_vec[0].ID, 1);
            EXPECT_EQ(s_vec[0].Name, "test2");
        }
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();
        auto u = q.NewFields();

        auto res = q.Limit(1).Order(u.ID.Desc()).Update(u.Age.Value(100), u.Name.Value("test3"));
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(UPDATE `user` SET `age` = ?, `name` = ? ORDER BY `id` DESC LIMIT 1;)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[100, test3]");
        EXPECT_EQ(fields, expected_fields);

        {
            auto res = q.Where(u.Age.Eq(100)).Find();
            auto s_vec = std::move(res.Value());
            EXPECT_EQ(s_vec.size(), 1);
            EXPECT_EQ(s_vec[0].ID, 20);
            EXPECT_EQ(s_vec[0].Name, "test3");
        }
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, QueryFieldsBuilder_Update_3) {
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
        for (int i = 1; i <= 20; i++) {
            auto user = model::User().SetID(i).SetName("test").SetAge(i).SetInsertTimestamp(
                    fmt::format("2022-09-{} 11:00:00", i));
            auto insert_res = orm->Insert(&user);
            EXPECT_TRUE(insert_res.IsOK());
        }
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();
        auto u = q.NewFields();

        auto res = q.Update(u.Age.Value(99), u.Name.Value("test2"));
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string(R"(UPDATE `user` SET `age` = ?, `name` = ?;)");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[99, test2]");
        EXPECT_EQ(fields, expected_fields);

        {
            auto res = q.Where(u.Age.Eq(99)).Find();
            auto s_vec = std::move(res.Value());
            EXPECT_EQ(s_vec.size(), 20);
        }
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}

TEST_F(ORMXXTest, QueryFieldsBuilder_Delete) {
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
        for (int i = 1; i <= 20; i++) {
            auto user = model::User().SetID(i).SetName("test").SetAge(i).SetInsertTimestamp(
                    fmt::format("2022-09-{} 11:00:00", i));
            auto insert_res = orm->Insert(&user);
            EXPECT_TRUE(insert_res.IsOK());
        }
    }

    {
        auto q = orm->NewQueryBuilder<model::User>();

        auto res = q.Delete();
        EXPECT_TRUE(res.IsOK());

        const auto& last_sql = orm->getLastSQLStatement();

        const auto& sql = last_sql.GetSQLString();
        const auto expected_sql = std::string("DELETE FROM `user`;");
        EXPECT_EQ(sql, expected_sql);

        const auto fields = last_sql.FieldsToString();
        const auto expected_fields = std::string("[]");
        EXPECT_EQ(fields, expected_fields);

        {
            auto res = q.Find();
            auto s_vec = std::move(res.Value());
            EXPECT_EQ(s_vec.size(), 0);
        }
    }

    {
        auto res = orm->DropTable<model::User>();
        EXPECT_TRUE(res.IsOK());
    }
}
