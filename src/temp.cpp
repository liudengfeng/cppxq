#include <gtest/gtest.h>

#include "test_cases.hpp"
#include "move_maps.hpp"
#include "xqboard.hpp"

TEST(MoveHistory, Runx1)
{
    moveVec_t history = {make_move("5635"), make_move("8765"), make_move("1234"), make_move("4586")};
    // 红先
    bool red_first = false;
    std::string view_str;
    int i = 0;
    if (!red_first)
    {
        i = 1;
        view_str += "    ";
    }
    for (auto &m : history)
    {
        if (i % 2 == 0)
        {
            view_str += fmt::format(fg(fmt::color::red), "{}", m.toString());
        }
        else
        {
            view_str += fmt::format(fg(fmt::color::sea_green), "-{}\n", m.toString());
        }
        i += 1;
    }
    fmt::print("{}\n", view_str);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}