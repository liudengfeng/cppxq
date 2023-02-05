#include <gtest/gtest.h>
#include <fstream>

#include "utils.hpp"

#include "test_cases.hpp"
#include "test_helper.hpp"

#include "xqboard.hpp"

TEST(Xqboard, Runx01)
{
    XqBoard b;
    b.set_pieces(rule_china_06);
    moveVec_t moves = {make_move("5040"), make_move("4858"), make_move("4050"), make_move("5848")};
    for (auto i = 0; i < MAX_NUM_VIOLATION; i++)
    {
        for (auto &m : moves)
        {
            b.step(m);
        }
    }
    // b.show_board();
    auto t = b.repetition_size();
    EXPECT_EQ(t, 4);
    EXPECT_EQ(b.final_result(), -1);
    EXPECT_TRUE(b.is_multi_repetitive(t, MAX_NUM_VIOLATION));
}

TEST(Xqboard, Runx02)
{
    XqBoard b;
    b.set_pieces(rule_china_14);
    moveVec_t moves = {make_move("6676"), make_move("7767"), make_move("7666"), make_move("6777")};
    for (auto i = 0; i < MAX_NUM_VIOLATION; i++)
    {
        for (auto &m : moves)
        {
            b.step(m);
        }
    }
    // b.show_board();
    auto t = b.repetition_size();
    EXPECT_EQ(t, 4);
    EXPECT_EQ(b.final_result(), 1);
    EXPECT_TRUE(b.is_multi_repetitive(t, MAX_NUM_VIOLATION));
}

TEST(Xqboard, Runx03)
{
    XqBoard b;
    b.set_pieces(rule_china_18);
    moveVec_t moves = {make_move("4434"), make_move("3949"), make_move("3444"), make_move("4939")};
    for (auto i = 0; i < MAX_NUM_VIOLATION; i++)
    {
        for (auto &m : moves)
        {
            b.step(m);
        }
    }
    // b.show_board();
    auto t = b.repetition_size();
    EXPECT_EQ(t, 4);
    EXPECT_EQ(b.final_result(), 0);
    EXPECT_TRUE(b.is_multi_repetitive(t, MAX_NUM_VIOLATION));
}

TEST(Xqboard, Runx04)
{
    XqBoard b;
    b.set_pieces(rule_china_208);
    moveVec_t moves = {make_move("2928"), make_move("3839"), make_move("2829"), make_move("3938"),
                       make_move("2989"), make_move("8373"), make_move("8979"), make_move("7383"),
                       make_move("7989"), make_move("8373"), make_move("8979"), make_move("7383"),
                       make_move("7973"), make_move("8388"), make_move("7370"), make_move("8881"),
                       make_move("7073"), make_move("8184")};

    for (auto &m : moves)
    {
        b.step(m);
    }

    // b.show_board();
    moveVec_t recent = b.get_last_moves(18);
    auto b1 = recent.back();
    auto b2 = recent[16];
    auto b3 = recent[15];
    // 检查尾部移动已经标注
    EXPECT_TRUE(b1.info.marked);
    EXPECT_EQ(b1.info.move_t, MoveType::XIAN);
    EXPECT_TRUE(b2.info.marked);
    EXPECT_EQ(b2.info.move_t, MoveType::XIAN);
    // 检查尾部正常退出
    EXPECT_FALSE(b3.info.marked);
}

TEST(Xqboard, Runx05)
{
    XqBoard b;
    b.set_pieces(rule_china_208);
    moveVec_t moves = {make_move("2928"), make_move("3839"), make_move("2829"), make_move("3938"),
                       make_move("2989"), make_move("8373"), make_move("8979"), make_move("7383"),
                       make_move("7989"), make_move("8373"), make_move("8979"), make_move("7383"),
                       make_move("7973"), make_move("8380"), make_move("7370"), make_move("8083"),
                       make_move("7073"), make_move("8380")};

    for (auto &m : moves)
    {
        b.step(m);
    }

    // b.show_board();
    EXPECT_EQ(b.final_result(), -1);
}

TEST(Xqboard, Runx06)
{
    XqBoard b;
    b.set_pieces(rule_china_208);
    moveVec_t moves = {make_move("2927"), make_move("4454"),
                       make_move("2728"), make_move("3839"), make_move("2829"), make_move("3938"),
                       make_move("2989"), make_move("8373"), make_move("8979"), make_move("7383"),
                       make_move("7989"), make_move("8373"), make_move("8979"), make_move("7383"),
                       make_move("7973"), make_move("8380"), make_move("7370"), make_move("8083"),
                       make_move("7073")};
    for (auto &m : moves)
    {
        b.step(m);
    }

    // b.show_board();
    EXPECT_EQ(b.final_result(), -1);

    auto move = make_move("8380");
    EXPECT_ANY_THROW(b.step(move));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}