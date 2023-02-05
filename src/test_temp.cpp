#include <gtest/gtest.h>
#include <fstream>
#include <fmt/color.h>
#include "utils.hpp"

#include "test_cases.hpp"
#include "test_helper.hpp"

#include "xqboard.hpp"

TEST(Xqboard, Runx01)
{
    auto fen = "3ak1NrC/4a4/4b4/9/9/9/9/9/2p1r4/3K5 r - 118 0 1";
    XqBoard b;
    b.set_pieces(fen, true, true);
    auto flag = true;
    b.set_use_rule_flag(flag);
    b.show_board();

    moveVec_t moves = {
        make_move("8988"),
        make_move("2131"),
    };

    for (auto m : moves)
    {
        b.step(m);
    }

    b.show_board(true);
    fmt::print("{} {}\n", b.is_game_ended(), b.final_result());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}