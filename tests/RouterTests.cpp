#include <gtest/gtest.h>

#include "Routing/Router.h"
#include "Routing/PathMatch.h"
#include "Routing/Exceptions.h"

using Routing::Router;
using Routing::PathMatch;
using Routing::PathNotFoundException;
using Routing::InvalidPathException;


TEST(RouterTests, simple_path) {
    Router router;
    router.registerPath("/simple_path");
    ASSERT_NO_THROW(router.matchPath("/simple_path"));
}

TEST(RouterTests, two_level_path) {
    Router router;
    router.registerPath("/one/two");
    router.matchPath("/one/two");
}

TEST(RouterTests, path_with_var_number) {
    Router router;
    router.registerPath("/path/with/:dynamic_var");
    ASSERT_NO_THROW(router.matchPath("/path/with/123"));
}

TEST(RouterTests, path_with_var_string) {
    Router router;
    router.registerPath("/path/with/:dynamic_var");
    ASSERT_NO_THROW(router.matchPath("/path/with/string_var_value"));
}


class RouterMatchTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        router.registerPath("/simple_path");
        router.registerPath("/one/two");
        router.registerPath("/path/with/:dynamic_var");
        router.registerPath("/path/to/:one_var/and/:another_var");
    }

    Router router;
};

TEST_F(RouterMatchTests, match_test) {
    PathMatch match = router.matchPath("/simple_path");
    ASSERT_EQ(std::string("/simple_path"), match.pathTemplate());
}

TEST_F(RouterMatchTests, match_test_2) {
    PathMatch match = router.matchPath("/one/two");
    ASSERT_EQ(std::string("/one/two"), match.pathTemplate());
}

TEST_F(RouterMatchTests, match_test_3) {
    PathMatch match = router.matchPath("/path/with/1234");
    ASSERT_EQ(std::string("/path/with/:dynamic_var"), match.pathTemplate());
}

TEST_F(RouterMatchTests, match_test_4) {
    PathMatch match = router.matchPath("/path/to/1234/and/4321");
    ASSERT_EQ(std::string("/path/to/:one_var/and/:another_var"), match.pathTemplate());
}

TEST_F(RouterMatchTests, get_var_test_1) {
    PathMatch match = router.matchPath("/path/with/dynvar_123");
    ASSERT_EQ(std::string("dynvar_123"), match.getVar("dynamic_var"));
}

TEST_F(RouterMatchTests, get_var_test_2) {
    PathMatch match = router.matchPath("/path/to/dynvar_1/and/dynvar_2");
    ASSERT_EQ(std::string("dynvar_1"), match.getVar("one_var"));
    ASSERT_EQ(std::string("dynvar_2"), match.getVar("another_var"));
}

TEST(RouterValidTests, invalid_path_two_slashes) {
    Router router;
    ASSERT_THROW(router.registerPath("/invalid//path"), InvalidPathException);
}

TEST(RouterValidTests, invalid_path_no_first_slash) {
    Router router;
    ASSERT_THROW(router.registerPath("invalid//path"), InvalidPathException);
}

TEST(RouterValidTests, invalid_path_two_first_slashes) {
    Router router;
    ASSERT_THROW(router.registerPath("//invalid/path/"), InvalidPathException);
}

TEST(RouterValidTests, valid_path_slash_last) {
    Router router;
    ASSERT_NO_THROW(router.registerPath("/valid/path/"));
}

TEST(RouterValidTests, valid_path_with_one_dyn_var_1) {
    Router router;
    ASSERT_NO_THROW(router.registerPath("/valid/path/:var"));
}

TEST(RouterValidTests, valid_path_with_one_dyn_var_2) {
    Router router;
    ASSERT_NO_THROW(router.registerPath("/valid/:var/path"));
}

TEST(RouterValidTests, valid_path_with_two_dyn_vars) {
    Router router;
    ASSERT_NO_THROW(router.registerPath("/valid/:var1/path/:var2"));
}

TEST(RouterValidTests, valid_path_with_multiple_dyn_vars) {
    Router router;
    ASSERT_NO_THROW(router.registerPath("/valid/:var1/path/:var2/:var3/:var4"));
}