#include <vector>
#include <string>

#include <gtest/gtest.h>
#include "utils.hpp"

using namespace helper;

TEST(UtilsTest, testSplit)
{
    const std::string s("rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1");
    std::vector<std::string> expect1;
    expect1.push_back("rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR");
    expect1.push_back("w");
    expect1.push_back("-");
    expect1.push_back("-");
    expect1.push_back("0");
    expect1.push_back("1");
    auto actual1 = helper::split(s, ' ');
    for (size_t i = 0; i < expect1.size(); i++)
    {
        EXPECT_EQ(expect1[i], actual1[i]);
    }
    std::vector<std::string> expect2;
    expect2.push_back("rnbakabnr");
    expect2.push_back("9");
    expect2.push_back("1c5c1");
    expect2.push_back("p1p1p1p1p");
    expect2.push_back("9");
    expect2.push_back("9");
    expect2.push_back("P1P1P1P1P");
    expect2.push_back("1C5C1");
    expect2.push_back("9");
    expect2.push_back("RNBAKABNR w - - 0 1");
    auto actual2 = helper::split(s, '/');
    for (size_t i = 0; i < expect2.size(); i++)
    {
        EXPECT_EQ(expect2[i], actual2[i]);
    }
    EXPECT_EQ(actual2.size(), 10);
}

// TEST(UtilsTest, testPrint)
// {
//     print_debug("临时观察信息，正式运行时删除显示\n");
//     print_info("一般信息\n");
//     print_warning("警告信息\n");
//     print_tip("重要提示信息\n");
// }

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}