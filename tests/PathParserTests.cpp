#include <gtest/gtest.h>

#include <Routing/Details/PathTemplateParser.h>
#include <Routing/Exceptions.h>

using namespace Routing::Details;

TEST(PathParserTests, valid_path) {
    ASSERT_NO_THROW(PathTemplateParser("/valid/path"));
}

TEST(PathParserTests, valid_path_delim_last) {
    ASSERT_NO_THROW(PathTemplateParser("/valid/path/"));
}


TEST(PathParserTests, valid_path_with_one_dyn_var) {
    ASSERT_NO_THROW(PathTemplateParser("/valid/:var1/path"));
}

TEST(PathParserTests, valid_path_with_two_dyn_vars) {
    ASSERT_NO_THROW(PathTemplateParser("/valid/:var1/:var2/path"));
}

TEST(PathParserTests, valid_path_with_two_dyn_vars_2) {
    ASSERT_NO_THROW(PathTemplateParser("/valid/:var1/path/:var2"));
}

TEST(PathParserTests, invalid_path_no_first_slash) {
    ASSERT_THROW(PathTemplateParser("invalid"), Routing::InvalidPathException);
}

TEST(PathParserTests, invalid_path_two_slashes) {
    ASSERT_THROW(PathTemplateParser("/invalid//path"), Routing::InvalidPathException);
}

TEST(PathParserTests, invalid_path_two_slashes_first) {
    ASSERT_THROW(PathTemplateParser("//invalid/path"), Routing::InvalidPathException);
}

TEST(PathParserTests, invalid_path_two_slashes_last) {
    ASSERT_THROW(PathTemplateParser("invalid/path//"), Routing::InvalidPathException);
}

TEST(PathParserTests, invalid_path_empty) {
    ASSERT_THROW(PathTemplateParser(""), Routing::InvalidPathException);
}

TEST(PathParserTests, invalid_path_empty_2) {
    ASSERT_THROW(PathTemplateParser("//"), Routing::InvalidPathException);
}

TEST(PathParser, dyn_var_1) {
    PathTemplateParser parser("/path/:var");
    int pos = parser.getDynVarPos("var");
    ASSERT_EQ(1, pos);
}

TEST(PathParser, dyn_var_2) {
    PathTemplateParser parser("/path/:var/to/some/:var2");
    int pos = parser.getDynVarPos("var2");
    ASSERT_EQ(4, pos);
}

TEST(PathParser, dyn_var_pos_no_such_var) {
    PathTemplateParser parser("/path/:var/to/some/:var2");
    ASSERT_THROW(parser.getDynVarPos("var3"), Routing::NoSuchElementException);
}