#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <limits>
#include <optional>
#include <string>

#include "ormxx/internal/field_to_string.h"

using namespace ormxx;
using namespace ormxx::internal;

class FieldToStringTest : public testing::Test {
protected:
    virtual void SetUp() override {}

    virtual void TearDown() override {}
};

TEST_F(FieldToStringTest, test) {
    {
        int32_t a = std::numeric_limits<int32_t>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("-2147483648"));
    }

    {
        uint32_t a = std::numeric_limits<uint32_t>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("4294967295"));
    }

    {
        int64_t a = std::numeric_limits<int64_t>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("-9223372036854775808"));
    }

    {
        uint64_t a = std::numeric_limits<uint64_t>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("18446744073709551615"));
    }

    {
        float a = std::numeric_limits<float>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0.000000"));
    }

    {
        float a = std::numeric_limits<float>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("340282346638528859811704183484516925440.000000"));
    }

    {
        double a = std::numeric_limits<double>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0.000000"));
    }

    {
        double a = std::numeric_limits<double>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(
                s,
                std::string(
                        "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000"));
    }

    {
        bool a = true;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("1"));
    }

    {
        bool a = false;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0"));
    }

    {
        std::string a = "";
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string(R"('')"));
    }

    {
        std::string a = "hello";
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string(R"('hello')"));
    }
}

TEST_F(FieldToStringTest, const_test) {
    {
        const int32_t a = std::numeric_limits<int32_t>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("-2147483648"));
    }

    {
        const uint32_t a = std::numeric_limits<uint32_t>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("4294967295"));
    }

    {
        const int64_t a = std::numeric_limits<int64_t>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("-9223372036854775808"));
    }

    {
        const uint64_t a = std::numeric_limits<uint64_t>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("18446744073709551615"));
    }

    {
        const float a = std::numeric_limits<float>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0.000000"));
    }

    {
        const float a = std::numeric_limits<float>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("340282346638528859811704183484516925440.000000"));
    }

    {
        const double a = std::numeric_limits<double>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0.000000"));
    }

    {
        const double a = std::numeric_limits<double>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(
                s,
                std::string(
                        "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000"));
    }

    {
        const bool a = true;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("1"));
    }

    {
        const bool a = false;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0"));
    }

    {
        const std::string a = "";
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string(R"('')"));
    }

    {
        const std::string a = "hello";
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string(R"('hello')"));
    }
}

TEST_F(FieldToStringTest, optional_test) {
    {
        std::optional<int32_t> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        std::optional<int32_t> a = std::numeric_limits<int32_t>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("-2147483648"));
    }

    {
        std::optional<uint32_t> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        std::optional<uint32_t> a = std::numeric_limits<uint32_t>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("4294967295"));
    }

    {
        std::optional<int64_t> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        std::optional<int64_t> a = std::numeric_limits<int64_t>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("-9223372036854775808"));
    }

    {
        std::optional<uint64_t> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        std::optional<uint64_t> a = std::numeric_limits<uint64_t>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("18446744073709551615"));
    }

    {
        std::optional<float> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        std::optional<float> a = std::numeric_limits<float>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0.000000"));
    }

    {
        std::optional<float> a = std::numeric_limits<float>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("340282346638528859811704183484516925440.000000"));
    }

    {
        std::optional<double> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        std::optional<double> a = std::numeric_limits<double>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0.000000"));
    }

    {
        std::optional<double> a = std::numeric_limits<double>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(
                s,
                std::string(
                        "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000"));
    }

    {
        std::optional<bool> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        std::optional<bool> a = true;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("1"));
    }

    {
        std::optional<bool> a = false;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0"));
    }

    {
        std::optional<std::string> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        std::optional<std::string> a = "";
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string(R"('')"));
    }

    {
        std::optional<std::string> a = "hello";
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string(R"('hello')"));
    }
}

TEST_F(FieldToStringTest, const_optional_test) {
    {
        const std::optional<int32_t> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        const std::optional<int32_t> a = std::numeric_limits<int32_t>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("-2147483648"));
    }

    {
        const std::optional<uint32_t> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        const std::optional<uint32_t> a = std::numeric_limits<uint32_t>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("4294967295"));
    }

    {
        const std::optional<int64_t> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        const std::optional<int64_t> a = std::numeric_limits<int64_t>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("-9223372036854775808"));
    }

    {
        const std::optional<uint64_t> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        const std::optional<uint64_t> a = std::numeric_limits<uint64_t>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("18446744073709551615"));
    }

    {
        const std::optional<float> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        const std::optional<float> a = std::numeric_limits<float>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0.000000"));
    }

    {
        const std::optional<float> a = std::numeric_limits<float>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("340282346638528859811704183484516925440.000000"));
    }

    {
        const std::optional<double> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        const std::optional<double> a = std::numeric_limits<double>::min();
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0.000000"));
    }

    {
        const std::optional<double> a = std::numeric_limits<double>::max();
        auto s = FieldToString(&a);
        EXPECT_EQ(
                s,
                std::string(
                        "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000"));
    }

    {
        const std::optional<bool> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        const std::optional<bool> a = true;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("1"));
    }

    {
        const std::optional<bool> a = false;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("0"));
    }

    {
        const std::optional<std::string> a = std::nullopt;
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string("NULL"));
    }

    {
        const std::optional<std::string> a = "";
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string(R"('')"));
    }

    {
        const std::optional<std::string> a = "hello";
        auto s = FieldToString(&a);
        EXPECT_EQ(s, std::string(R"('hello')"));
    }
}
