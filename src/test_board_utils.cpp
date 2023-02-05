#include <gtest/gtest.h>

#include "test_cases.hpp"
#include "board_utils.hpp"

#include "test_helper.hpp"

using namespace rule2022;

// [==========] Running 24 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 24 tests from BoardUtils
// [ RUN      ] BoardUtils.Eatsx01x1
// [       OK ] BoardUtils.Eatsx01x1 (0 ms)
// [ RUN      ] BoardUtils.Eatsx01x2
// [       OK ] BoardUtils.Eatsx01x2 (0 ms)
// [ RUN      ] BoardUtils.Eatsx01x3
// [       OK ] BoardUtils.Eatsx01x3 (0 ms)
// [ RUN      ] BoardUtils.Eatsx01x4
// [       OK ] BoardUtils.Eatsx01x4 (1 ms)
// [ RUN      ] BoardUtils.Eatsx01x5
// [       OK ] BoardUtils.Eatsx01x5 (0 ms)
// [ RUN      ] BoardUtils.Eatsx02x1
// [       OK ] BoardUtils.Eatsx02x1 (0 ms)
// [ RUN      ] BoardUtils.Eatsx02x2
// [       OK ] BoardUtils.Eatsx02x2 (0 ms)
// [ RUN      ] BoardUtils.Eatsx02x3
// [       OK ] BoardUtils.Eatsx02x3 (1 ms)
// [ RUN      ] BoardUtils.Eatsx02x4
// [       OK ] BoardUtils.Eatsx02x4 (1 ms)
// [ RUN      ] BoardUtils.Eatsx03x1
// [       OK ] BoardUtils.Eatsx03x1 (0 ms)
// [ RUN      ] BoardUtils.Eatsx04x1
// [       OK ] BoardUtils.Eatsx04x1 (0 ms)
// [ RUN      ] BoardUtils.Eatsx04x2
// [       OK ] BoardUtils.Eatsx04x2 (1 ms)
// [ RUN      ] BoardUtils.Eatsx04x3
// [       OK ] BoardUtils.Eatsx04x3 (0 ms)
// [ RUN      ] BoardUtils.Eatsx04x4
// [       OK ] BoardUtils.Eatsx04x4 (1 ms)
// [ RUN      ] BoardUtils.Duix01x1
// [       OK ] BoardUtils.Duix01x1 (0 ms)
// [ RUN      ] BoardUtils.Duix01x2
// [       OK ] BoardUtils.Duix01x2 (1 ms)
// [ RUN      ] BoardUtils.Duix02x1
// [       OK ] BoardUtils.Duix02x1 (1 ms)
// [ RUN      ] BoardUtils.Duix02x2
// [       OK ] BoardUtils.Duix02x2 (2 ms)
// [ RUN      ] BoardUtils.Duix03
// [       OK ] BoardUtils.Duix03 (0 ms)
// [ RUN      ] BoardUtils.Duix04
// [       OK ] BoardUtils.Duix04 (2 ms)
// [ RUN      ] BoardUtils.Duix05
// [       OK ] BoardUtils.Duix05 (0 ms)
// [ RUN      ] BoardUtils.JJSortx01
// [       OK ] BoardUtils.JJSortx01 (18 ms)
// [ RUN      ] BoardUtils.JJSortx02
// [       OK ] BoardUtils.JJSortx02 (6 ms)
// [ RUN      ] BoardUtils.JJSortx03
// [       OK ] BoardUtils.JJSortx03 (13 ms)
// [----------] 24 tests from BoardUtils (62 ms total)

// [----------] Global test environment tear-down
// [==========] 24 tests from 1 test suite ran. (62 ms total)
// [  PASSED  ] 24 tests.

// 走子后本方可吃
TEST(BoardUtils, Eatsx01x1)
{
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 1);
    EXPECT_TRUE(contains(related, make_move("1252")));
}

TEST(BoardUtils, Eatsx01x2)
{
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 1);
    // 按吃子价值从大到小排序
    EXPECT_EQ(related[0], make_move("5646"));
    // 排除车原本可吃目标
    EXPECT_FALSE(contains(related, make_move("5650")));
}

TEST(BoardUtils, Eatsx01x3)
{
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256"), make_move("1216")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    // 不存在相关吃
    EXPECT_EQ(related.size(), 0);
}

TEST(BoardUtils, Eatsx01x4)
{
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256"), make_move("1216"), make_move("5652")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 2);
    // 按吃子价值从大到小排序
    EXPECT_EQ(related[0], make_move("5242"));
    EXPECT_EQ(related[1], make_move("5262"));
}

// 同等价值，优先最后落子的吃
TEST(BoardUtils, Eatsx01x5)
{
    Board b;
    b.set_pieces(rule_china_23);
    moveVec_t moves = {make_move("2122")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 1);
    // 按吃子价值从大到小排序
    EXPECT_EQ(related[0], make_move("2212"));
}

TEST(BoardUtils, Eatsx02x1)
{
    Board b;
    b.set_pieces(rule_china_09);
    moveVec_t moves = {make_move("6472")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 2);
    EXPECT_TRUE(contains(related, make_move("7280")));
}

TEST(BoardUtils, Eatsx02x2)
{
    Board b;
    b.set_pieces(rule_china_09);
    moveVec_t moves = {make_move("6472"), make_move("8070")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 1);
    // 底线炮与车同水平线，车非其炮架，不相关
    EXPECT_TRUE(contains(related, make_move("7072")));
}

TEST(BoardUtils, Eatsx02x3)
{
    Board b;
    b.set_pieces(rule_china_09);
    moveVec_t moves = {make_move("6472"), make_move("8070"), make_move("7264")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 1);
    EXPECT_TRUE(contains(related, make_move("7670")));
}

TEST(BoardUtils, Eatsx02x4)
{
    Board b;
    b.set_pieces(rule_china_09);
    moveVec_t moves = {make_move("6472"), make_move("8070"), make_move("7264"), make_move("7080")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 1);
    EXPECT_TRUE(contains(related, make_move("8083")));
}

TEST(BoardUtils, Eatsx03x1)
{
    Board b;
    b.set_pieces(rule_china_25);
    moveVec_t moves = {make_move("3435")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 1);
    EXPECT_TRUE(contains(related, make_move("3555")));
    EXPECT_FALSE(contains(related, make_move("3539")));
    // 以下不考虑
    // 黑方底线马与车所捉对象相同，列入相关
    // EXPECT_TRUE(contains(related, make_move("3339")));
    // EXPECT_TRUE(contains(related, make_move("1939")));
}

TEST(BoardUtils, Eatsx04x1)
{
    Board b;
    b.set_pieces(rule_china_215);
    moveVec_t moves = {make_move("3331")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 1);
    EXPECT_TRUE(contains(related, make_move("3171")));
}

TEST(BoardUtils, Eatsx04x2)
{
    Board b;
    b.set_pieces(rule_china_215);
    moveVec_t moves = {make_move("3331"), make_move("7173")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 1);
    EXPECT_TRUE(contains(related, make_move("7383")));
}

TEST(BoardUtils, Eatsx04x3)
{
    Board b;
    b.set_pieces(rule_china_27);
    moveVec_t moves = {make_move("1628"), make_move("0908")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related);
    EXPECT_EQ(related.size(), 0);
    // EXPECT_TRUE(contains(related, make_move("0100")));
}

// 走子方的对手
TEST(BoardUtils, Eatsx04x4)
{
    Board b;
    b.set_pieces(rule_china_215);
    b.SetPlayer(S_BLACK);
    moveVec_t moves = {make_move("6562")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "测试相关吃");
    auto related1 = related_eat_after_moved(b, false);
    // fmt::print("{}\n", related1);
    EXPECT_EQ(related1.size(), 1);
    EXPECT_TRUE(contains(related1, make_move("6202")));

    // 只考虑直接变化
    auto related2 = related_eat_after_moved(b, true);
    // fmt::print("{}\n", related2);
    EXPECT_EQ(related2.size(), 0);
    // EXPECT_TRUE(contains(related2, make_move("5363")));
}

// 注意相关吃：将军属性迁移问题
// TEST(BoardUtils, JJOfEatsx01)
// {
//     Board b;
//     b.set_pieces(rule_china_16);
//     moveVec_t moves = {make_move("7679"), make_move("5958"), make_move("7976")};
//     for (auto &m : moves)
//     {
//         b.DoMove(m);
//     }
//     Color player = S_RED;
//     b.SetPlayer(player);
//     moves = {make_move("7656"), make_move("4857")};
//     for (auto &m : moves)
//     {
//         b.DoMove(m);
//     }
//     // b.show_board();
//     auto tgt = make_move("5646");
//     auto new_eats = b.GetCandidatesForEat(player, true);
//     auto it = std::find(new_eats.begin(), new_eats.end(), tgt);
//     EXPECT_TRUE((*it).is_check());
// }

TEST(BoardUtils, Duix01x1)
{
    Coord dui;
    Board b;
    b.set_pieces(rule_china_02);
    moveVec_t moves = {make_move("7684")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑坐标");

    // 不存在兑坐标
    dui = get_dui_coord(b);
    EXPECT_EQ(dui, EMPTY_COORD);
}

TEST(BoardUtils, Duix01x2)
{
    Coord dui;
    Board b;
    b.set_pieces(rule_china_02);
    moveVec_t moves = {make_move("7684"), make_move("8979")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑坐标");

    dui = get_dui_coord(b);
    EXPECT_EQ(dui, Coord(7, 9));
}

TEST(BoardUtils, Duix02x1)
{
    Coord dui;
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑坐标");

    dui = get_dui_coord(b);
    EXPECT_EQ(dui, Coord(2, 7));
}

TEST(BoardUtils, Duix02x2)
{
    Coord dui;
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256"), make_move("1216")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑坐标");

    dui = get_dui_coord(b);
    EXPECT_EQ(dui, Coord(4, 6));
}

TEST(BoardUtils, Duix03)
{
    Coord dui;
    Board b;
    b.set_pieces(rule_china_13);
    moveVec_t moves = {make_move("4636"), make_move("3949"), make_move("3646")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑坐标");

    dui = get_dui_coord(b);
    EXPECT_EQ(dui, Coord(4, 5));
}

TEST(BoardUtils, Duix04)
{
    Coord dui;
    Board b;
    b.set_pieces(rule_china_204);
    moveVec_t moves = {make_move("1716"), make_move("2708"), make_move("1617"), make_move("0827")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑坐标");

    dui = get_dui_coord(b);
    EXPECT_EQ(dui, Coord(4, 7));
}

TEST(BoardUtils, Duix05)
{
    Coord dui;
    Board b;
    b.set_pieces(rule_china_20);
    moveVec_t moves = {make_move("1608")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑坐标");

    dui = get_dui_coord(b);
    EXPECT_EQ(dui, Coord(0, 6));
}

// // 可吃将军棋子的移动候选
// TEST(BoardUtils, ECCx01)
// {
//     Board b;
//     Color player = S_BLACK;
//     b.set_pieces("7R1/3ka4/3a5/9/9/4p4/8c/4B1r2/4A4/3A1KB2 w - - 0 1");
//     b.SetPlayer(player);
//     moveVec_t moves = {make_move("8380"), make_move("7970"), make_move("6242")};
//     for (auto &m : moves)
//     {
//         b.DoMove(m);
//     }

//     // b.show_board(true, "吃将军棋子");
//     auto cands = eat_checked_cands(b);
//     // fmt::print("{}\n", cands);
//     EXPECT_EQ(cands.size(), 1);
//     EXPECT_EQ(cands[0], make_move("7080"));
// }

TEST(BoardUtils, JJSortx01)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_09);
    moveVec_t moves = {make_move("6472"), make_move("8070")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto jjs = b.GetCandidatesForCheck(player);
    sorted_jj_cands(b, player, jjs);
    auto expected = make_move("6062");
    EXPECT_EQ(jjs[0], expected);
}

TEST(BoardUtils, JJSortx02)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_214);
    moveVec_t moves = {make_move("8261"), make_move("8070")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto jjs = b.GetCandidatesForCheck(player);
    sorted_jj_cands(b, player, jjs);
    auto expected = make_move("6030");
    EXPECT_EQ(jjs[0], expected);
}

// 补充：将军同时吃子价值也要考虑
TEST(BoardUtils, JJSortx03)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_28);
    moveVec_t moves = {make_move("1929")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto jjs = b.GetCandidatesForCheck(player);
    // fmt::print("排序前 {}\n", jjs);
    sorted_jj_cands(b, player, jjs);
    // fmt::print("排序后 {}\n", jjs);
    auto expected = make_move("2927");
    EXPECT_EQ(jjs[0], expected);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}