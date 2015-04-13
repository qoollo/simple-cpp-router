#include <gtest/gtest.h>

#include <Routing/Details/RegexConverter.h>

using namespace Routing::Details;

TEST(RegexConverterTests, converting_slashes) {
    std::string expected = "\\/test\\/path";

    RegexConverter converter;
    std::string result = converter.toRegex("/test/path");

    ASSERT_EQ(expected, result);
}

TEST(RegexConverterTests, replacing_dynamic_vars_1) {
    std::string expected = "\\/test\\/[^\\/]+";

    RegexConverter converter;
    std::string result = converter.toRegex("/test/:var1");

    ASSERT_EQ(expected, result);
}

TEST(RegexConverterTests, replacing_dynamic_vars_2) {
    std::string expected = "\\/test\\/[^\\/]+\\/test";

    RegexConverter converter;
    std::string result = converter.toRegex("/test/:var1/test");

    ASSERT_EQ(expected, result);
}

TEST(RegexConverterTests, replacing_dynamic_vars_3) {
    std::string expected = "\\/[^\\/]+\\/test";

    RegexConverter converter;
    std::string result = converter.toRegex("/:var/test");

    ASSERT_EQ(expected, result);
}

TEST(RegexConverterTests, replacing_dynamic_vars_4) {
    std::string expected = "\\/[^\\/]+\\/";

    RegexConverter converter;
    std::string result = converter.toRegex("/:var/");

    ASSERT_EQ(expected, result);
}

TEST(RegexConverterTests, replacing_dynamic_vars_5) {
    std::string expected = "\\/[^\\/]+";

    RegexConverter converter;
    std::string result = converter.toRegex("/:var");

    ASSERT_EQ(expected, result);
}

TEST(RegexConverterTests, replacing_dynamic_vars_multiple) {
    std::string expected = "\\/test\\/[^\\/]+\\/[^\\/]+";

    RegexConverter converter;
    std::string result = converter.toRegex("/test/:var1/:var2");

    ASSERT_EQ(expected, result);
}

TEST(RegexConverterTests, replacing_dynamic_vars_multiple_2) {
    std::string expected = "\\/test\\/[^\\/]+\\/no_var\\/[^\\/]+";

    RegexConverter converter;
    std::string result = converter.toRegex("/test/:var1/no_var/:var2");

    ASSERT_EQ(expected, result);
}