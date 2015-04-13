#include <gtest/gtest.h>
#include <Routing/Details/StringTokenizer.h>
#include <vector>

using namespace Routing::Details;

TEST(StringTokenizerTests, route_tokenize) {
    std::string str = "/this/will/be/tokenized";

    std::vector<std::string> expected {
        "this", "will", "be", "tokenized"
    };

    char delim = '/';

    std::vector<std::string> result = StringTokenizer(str,delim).getAllTokens();
    ASSERT_EQ(expected, result);
}

TEST(StringTokenizerTests, delimeter_last) {
    std::string str = "/tokenize/me/";
    std::vector<std::string> expected = {
        "tokenize", "me"
    };

    char delim = '/';

    std::vector<std::string> result = StringTokenizer(str,delim).getAllTokens();

    ASSERT_EQ(expected, result);
}

TEST(StringTokenizerTests, double_delimeter) {
    std::string str = "/tokenize//me";
    std::vector<std::string> expected = {
        "tokenize", "", "me"
    };

    char delim = '/';

    std::vector<std::string> result = StringTokenizer(str,delim).getAllTokens();

    ASSERT_EQ(expected, result);
}

TEST(StringTokenizerTests, token_by_index_1) {
    StringTokenizer tokenizer("/path/:var1/:var2", '/');
    ASSERT_EQ(":var1", tokenizer.getToken(1));
}