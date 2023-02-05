#include <gtest/gtest.h>

#include "test_cases.hpp"
#include "xqboard.hpp"

// [==========] Running 5 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 5 tests from TestMarkUtils
// [ RUN      ] TestMarkUtils.Duix01
// [       OK ] TestMarkUtils.Duix01 (3 ms)
// [ RUN      ] TestMarkUtils.Duix02x1
// [       OK ] TestMarkUtils.Duix02x1 (14 ms)
// [ RUN      ] TestMarkUtils.Duix02x2
// [       OK ] TestMarkUtils.Duix02x2 (77 ms)
// [ RUN      ] TestMarkUtils.Offlinex01
// [       OK ] TestMarkUtils.Offlinex01 (1 ms)
// [ RUN      ] TestMarkUtils.Offlinex02
// [       OK ] TestMarkUtils.Offlinex02 (1 ms)
// [----------] 5 tests from TestMarkUtils (97 ms total)

// [----------] Global test environment tear-down
// [==========] 5 tests from 1 test suite ran. (97 ms total)
// [  PASSED  ] 5 tests.

TEST(TestMarkUtils, Duix01)
{
    Board b;
    b.set_pieces(rule_china_13);
    moveVec_t moves = {make_move("4636"), make_move("3949"), make_move("3646")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑路径");
    auto dui_move = get_dui_move(b);
    EXPECT_EQ(dui_move, make_move("4745"));

    auto dui = get_dui_coord(b);

    auto hist = get_dui_history(b, dui, dui_move);
    // fmt::print("{}\n", hist);
    EXPECT_EQ(hist.size(), 2);
    moveVec_t expected = {make_move("4745"), make_move("3545")};
    EXPECT_EQ(hist, expected);
}

TEST(TestMarkUtils, Duix02x1)
{
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑路径");
    auto dui_move = get_dui_move(b);
    EXPECT_EQ(dui_move, make_move("4627"));

    auto dui = get_dui_coord(b);
    auto hist = get_dui_history(b, dui, dui_move);
    // fmt::print("{}\n", hist);
    EXPECT_EQ(hist.size(), 2);
    // 理论上，以下路径亦可。
    // moveVec_t expected = {make_move("4627"), make_move("8727"), make_move("4247"), make_move("2947")};
    moveVec_t expected = {make_move("4627"), make_move("8727")};
    EXPECT_EQ(hist, expected);
}

TEST(TestMarkUtils, Duix02x2)
{
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256"), make_move("1216")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "兑路径");
    auto dui_move = get_dui_move(b);
    EXPECT_EQ(dui_move, make_move("2746"));

    auto dui = get_dui_coord(b);
    auto hist = get_dui_history(b, dui, dui_move);
    // // fmt::print("{}\n", hist);
    EXPECT_EQ(hist.size(), 2);
    moveVec_t expected = {make_move("2746"), make_move("4246")};
    EXPECT_EQ(hist, expected);
}

TEST(TestMarkUtils, Offlinex01)
{
    Board b;
    b.set_pieces(rule_china_239);
    moveVec_t moves = {make_move("6766"), make_move("4654"), make_move("6667")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    Color player = OPPONENT(b.next_player());
    auto cands = b.GetCandidatesByPlayer(player);
    auto eat = get_can_not_offline_eat(b, cands);
    Move expected = make_move("7858");
    EXPECT_EQ(eat, expected);
}

TEST(TestMarkUtils, Offlinex02)
{
    Board b;
    b.set_pieces(rule_china_249);
    moveVec_t moves = {make_move("1628")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    Color player = OPPONENT(b.next_player());
    auto cands = b.GetCandidatesByPlayer(player);
    auto eat = get_can_not_offline_eat(b, cands);
    Move expected = make_move("6838");
    EXPECT_EQ(eat, expected);
}

// TEST(TestMarkUtils, Runx1)
// {
//     Board b;
//     Move moved;
//     b.set_pieces(rule_china_18);
//     // b.show_board();

//     moved = make_move("4434");
//     b.DoMove(moved);

//     moved = make_move("3949");
//     b.DoMove(moved);

//     moved = make_move("3444");
//     b.DoMove(moved);

//     moved.info.move_t = MoveType::ZHUO;
//     moved.info.zhuo_tgt.piece = PieceType::ELEPHANT;

//     EXPECT_TRUE(is_SH_ZSX(b, moved));
// }

// // // 避吃捉子【不存在相关吃的前提下】
// // TEST(TestMarkUtils, Runx2)
// // {
// //     Board b;
// //     Move moved;
// //     b.set_pieces(rule_china_12);
// //     // b.show_board();

// //     moved = make_move("8676");
// //     b.DoMove(moved);

// //     moved = make_move("7787");
// //     b.DoMove(moved);

// //     bool ended = false;
// //     // 走子后可吃其他棋子
// //     _zhuo_avoid_eated(b, moved, ended);
// //     EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
// //     EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::PAWN);
// // }

// // 可保护最后一步被吃的棋子
// TEST(TestMarkUtils, Runx3)
// {
//     Board b;
//     Move moved;
//     b.set_pieces(rule_china_03);

//     moved = make_move("3121");
//     b.DoMove(moved);
//     EXPECT_TRUE(is_can_protected_last_eated(b));
// }

// // 获取断根捉子移动
// TEST(TestMarkUtils, Runx4)
// {
//     Board b;
//     Move moved;
//     b.set_pieces(rule_china_03);

//     moved = make_move("4260");
//     b.DoMove(moved);

//     Move expected = make_move("3121");
//     auto actual = get_cut_root_eat(b);
//     // fmt::print("{}\n", actual);
//     EXPECT_EQ(expected, actual);
// }

// // 共同攻击点
// TEST(TestMarkUtils, Runx5x1)
// {
//     Board b;
//     Move moved;
//     b.set_pieces(rule_china_25);
//     // b.show_board();

//     moved = make_move("3435");
//     b.DoMove(moved);

//     Coord expected{3, 9};
//     auto actual = get_common_attack(b, moved);
//     // fmt::print("{}\n", actual);
//     EXPECT_EQ(expected, actual);
// }

// TEST(TestMarkUtils, Runx5x2)
// {
//     Board b;
//     Move moved;
//     b.set_pieces(rule_china_245);
//     // b.show_board();

//     moved = make_move("6989");
//     b.DoMove(moved);

//     moved = make_move("8867");
//     b.DoMove(moved);

//     moved = make_move("8969");
//     b.DoMove(moved);

//     Coord expected{6, 5};
//     auto actual = get_common_attack(b, moved);
//     // fmt::print("{}\n", actual);
//     EXPECT_EQ(expected, actual);
// }

// TEST(TestMarkUtils, Runx7x1)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130")};
//     moves[0].info.move_t = MoveType::JIANG;
//     moves[1].info.move_t = MoveType::JIANG;
//     EXPECT_TRUE(is_prohibit_group(moves));
// }

// TEST(TestMarkUtils, Runx7x2)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130")};
//     moves[0].info.move_t = MoveType::SHA;
//     moves[1].info.move_t = MoveType::SHA;
//     EXPECT_TRUE(is_prohibit_group(moves));
// }

// TEST(TestMarkUtils, Runx7x3)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130")};
//     moves[0].info.move_t = MoveType::ZHUO;
//     moves[1].info.move_t = MoveType::ZHUO;
//     EXPECT_TRUE(is_prohibit_group(moves));
// }

// TEST(TestMarkUtils, Runx7x4)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130")};
//     moves[0].info.move_t = MoveType::JIANG;
//     moves[1].info.move_t = MoveType::SHA;
//     EXPECT_TRUE(is_prohibit_group(moves));
// }

// TEST(TestMarkUtils, Runx7x5)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130")};
//     moves[0].info.move_t = MoveType::SHA;
//     moves[1].info.move_t = MoveType::JIANG;
//     EXPECT_TRUE(is_prohibit_group(moves));
// }

// TEST(TestMarkUtils, Runx7x6)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130")};
//     moves[0].info.move_t = MoveType::JIANG;
//     moves[1].info.move_t = MoveType::ZHUO;
//     EXPECT_TRUE(is_prohibit_group(moves));
// }

// TEST(TestMarkUtils, Runx7x7)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130")};
//     moves[0].info.move_t = MoveType::SHA;
//     moves[1].info.move_t = MoveType::ZHUO;
//     EXPECT_TRUE(is_prohibit_group(moves));
// }

// TEST(TestMarkUtils, Runx7x8)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130")};
//     moves[0].info.move_t = MoveType::XIAN;
//     moves[1].info.move_t = MoveType::ZHUO;
//     EXPECT_FALSE(is_prohibit_group(moves));
// }

// TEST(TestMarkUtils, Runx7x9)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130"), make_move("4130")};
//     moves[0].info.move_t = MoveType::XIAN;
//     moves[1].info.move_t = MoveType::ZHUO;
//     moves[2].info.move_t = MoveType::ZHUO;
//     EXPECT_FALSE(is_prohibit_group(moves));
// }

// TEST(TestMarkUtils, Runx8x1)
// {
//     moveVec_t moves = {make_move("3343"), make_move("4130")};
//     moves[0].info.move_t = MoveType::ZHUO;
//     moves[0].info.no_root_protected = true;
//     moves[1].info.move_t = MoveType::JIANG;
//     EXPECT_TRUE(should_change(moves));
// }

// // 测试走子前可捉子列表
// TEST(TestMarkUtils, Runx9x1)
// {
//     Board b;
//     Move moved;
//     b.set_pieces(rule_china_05);

//     // 车七退五（闲）
//     moved = make_move("2924");
//     b.DoMove(moved);

//     auto actual = get_zhuo_objects_before_moved(b);

//     b.undoMove();
//     // 走子获得详细信息
//     // 直接吃士
//     moved = make_move("2959");
//     b.DoMove(moved);
//     moveVec_t expected = {moved};

//     EXPECT_EQ(actual, expected);
// }

// TEST(TestMarkUtils, Runx9x2)
// {
//     Board b;
//     Move moved;
//     b.set_pieces(rule_china_206);

//     // 车七退五（闲）
//     moved = make_move("0907");
//     b.DoMove(moved);

//     auto actual = get_zhuo_objects_before_moved(b);

//     // auto player = S_RED;
//     b.undoMove();
//     // 走子获得详细信息
//     // 将军吃士
//     auto moved1 = make_move("5859");
//     b.DoMove(moved1);

//     auto moved2 = make_move("4948");
//     b.DoMove(moved2);

//     // 车吃士
//     auto moved3 = make_move("0939");
//     b.DoMove(moved3);

//     moveVec_t expected = {moved1, moved2, moved3};

//     EXPECT_TRUE(_is_same_dz(actual, expected));
// }

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}