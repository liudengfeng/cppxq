#include <gtest/gtest.h>

#include "test_cases.hpp"

#include "xqboard.hpp"

// [==========] Running 31 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 31 tests from MarkMove
// [ RUN      ] MarkMove.Testx02
// [       OK ] MarkMove.Testx02 (87 ms)
// [ RUN      ] MarkMove.Testx03
// [       OK ] MarkMove.Testx03 (88 ms)
// [ RUN      ] MarkMove.Testx04
// [       OK ] MarkMove.Testx04 (24 ms)
// [ RUN      ] MarkMove.Testx05
// [       OK ] MarkMove.Testx05 (64 ms)
// [ RUN      ] MarkMove.Testx06
// [       OK ] MarkMove.Testx06 (1 ms)
// [ RUN      ] MarkMove.Testx07
// [       OK ] MarkMove.Testx07 (834 ms)
// [ RUN      ] MarkMove.Testx08
// [       OK ] MarkMove.Testx08 (25 ms)
// [ RUN      ] MarkMove.Testx09
// [       OK ] MarkMove.Testx09 (1005 ms)
// [ RUN      ] MarkMove.Testx10
// [       OK ] MarkMove.Testx10 (52 ms)
// [ RUN      ] MarkMove.Testx11
// [       OK ] MarkMove.Testx11 (21 ms)
// [ RUN      ] MarkMove.Testx12
// [       OK ] MarkMove.Testx12 (101 ms)
// [ RUN      ] MarkMove.Testx13
// [       OK ] MarkMove.Testx13 (79 ms)
// [ RUN      ] MarkMove.Testx14
// [       OK ] MarkMove.Testx14 (173 ms)
// [ RUN      ] MarkMove.Testx15
// [       OK ] MarkMove.Testx15 (5 ms)
// [ RUN      ] MarkMove.Testx16
// [       OK ] MarkMove.Testx16 (96 ms)
// [ RUN      ] MarkMove.Testx17
// [       OK ] MarkMove.Testx17 (484 ms)
// [ RUN      ] MarkMove.Testx18
// [       OK ] MarkMove.Testx18 (6 ms)
// [ RUN      ] MarkMove.Testx19
// [       OK ] MarkMove.Testx19 (57 ms)
// [ RUN      ] MarkMove.Testx20
// [       OK ] MarkMove.Testx20 (38 ms)
// [ RUN      ] MarkMove.Testx21
// [       OK ] MarkMove.Testx21 (240 ms)
// [ RUN      ] MarkMove.Testx22
// [       OK ] MarkMove.Testx22 (21 ms)
// [ RUN      ] MarkMove.Testx23
// [       OK ] MarkMove.Testx23 (44 ms)
// [ RUN      ] MarkMove.Testx24
// [       OK ] MarkMove.Testx24 (19 ms)
// [ RUN      ] MarkMove.Testx25
// [       OK ] MarkMove.Testx25 (806 ms)
// [ RUN      ] MarkMove.Testx26
// [       OK ] MarkMove.Testx26 (299 ms)
// [ RUN      ] MarkMove.Testx27
// [       OK ] MarkMove.Testx27 (41 ms)
// [ RUN      ] MarkMove.Testx28
// [       OK ] MarkMove.Testx28 (244 ms)
// [ RUN      ] MarkMove.Testx29x1
// [       OK ] MarkMove.Testx29x1 (191 ms)
// [ RUN      ] MarkMove.Testx29x2
// [       OK ] MarkMove.Testx29x2 (136 ms)
// [ RUN      ] MarkMove.Testx30x1
// [       OK ] MarkMove.Testx30x1 (237 ms)
// [ RUN      ] MarkMove.Testx30x2
// [       OK ] MarkMove.Testx30x2 (147 ms)
// [----------] 31 tests from MarkMove (5682 ms total)

// [----------] Global test environment tear-down
// [==========] 31 tests from 1 test suite ran. (5682 ms total)
// [  PASSED  ] 31 tests.

// 图2着法：
//   1. 马二退一（捉）   车9平8（兑）
//   2. 马一进二（捉）   车8平9 (捉）
//   红方退马打车，判捉，而进马伏下一步卧槽“将军”弃马得车，判捉。
//   红方长捉，黑方一捉一兑，红方变着，不变作负。
TEST(MarkMove, Testx02)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_02);

    moved = make_move("7684");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);
    Coord tgt{8, 9};
    EXPECT_EQ(moved.info.zhuo_tgt.coord, tgt);

    moved = make_move("8979");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("8476");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    moved = make_move("7989");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::CANNON);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图3着法：
//   1. 相五退三 （捉）  车8平7 （捉）
//   2. 相三进五 （捉）  车7平8 （捉）
//   红方进相、退相为断根捉马。黑方车7平8后，可以下一着开始运用连续将军得车，判捉。
//   红方长捉无根子，黑方长捉车，双方不变作和。
TEST(MarkMove, Testx03)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_03);

    moved = make_move("4260");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.no_root_protected);

    // 车８平７（捉）下一着开始运用连续“将军”得子
    moved = make_move("7161");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    moved = make_move("6042");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::HORSE);
    EXPECT_TRUE(moved.info.no_root_protected);

    moved = make_move("6171");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 图4着法：
//     1. 马四退六 （捉）  象9进7 （闲）
//     2. 马六进四 （捉）  象7退9 （闲）
//     红方退马捉象，进马则伏以炮换马多得一卒，判捉。红方长捉，黑方两闲，红方变着，不变作负。
TEST(MarkMove, Testx04)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_04);

    moved = make_move("5635");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ELEPHANT);

    moved = make_move("8765");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3556");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("6587");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图5着法：
//   1. 车七退五 （闲）  将5退1（闲）
//   2. 车七进五 （将)   将5进1 (闲）
//   红方退车前就可吃底士，退车后吃士结果没有发生变化，红方一将一闲，黑方两闲，双方不变作和。
TEST(MarkMove, Testx05)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_05);

    // 车七退五（闲）
    moved = make_move("2924");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    // 将５退１（闲）
    moved = make_move("4849");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    // 车七进五（将）
    moved = make_move("2429");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    // 将５进１（闲）
    moved = make_move("4948");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 图6着法：
//    1. 车四平五 （将）  将5平6  （闲）
//    2. 车五平四 （将）  将6平5  （闲）
//    尽管红方只有车能走动，无从变着，但在任何情况下均不允许单方面长将，红方作负。
TEST(MarkMove, Testx06)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_06);

    // 车四平五（将）
    moved = make_move("5040");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    // 将５平６（闲）
    moved = make_move("4858");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    // 车五平四（将）
    moved = make_move("4050");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    // 将６平５（闲）
    moved = make_move("5848");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 不能离线
// 图7着法：
//   1. 炮一平二 （杀） 车9平8 （拦）
//   2. 炮二平一 （杀） 车8平9 （拦）
//   红方两着平炮步步伏杀，属长杀。黑方两着平车拦阻看似捉炮，实则不能离线吃炮（红车可垫将还杀），判长拦。
//   红方长杀，黑方长拦。红方变着，不变作负。
// 📓 `拦`直接标记为`闲`
TEST(MarkMove, Testx07)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_07);

    // 炮一平二（杀）
    moved = make_move("8070");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    // 车９平８（拦）
    moved = make_move("8878");
    b.DoMove(moved);

    mark_move(b, moved);
    // 📓 `拦`直接标记为`闲`
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    // 炮二平一（杀）
    moved = make_move("7080");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    // // 车８平９（拦）
    moved = make_move("7888");
    b.DoMove(moved);

    mark_move(b, moved);
    // 📓 `拦`直接标记为`闲`
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图8着法：
//    1. 车二退六 （捉）  将6退1 （捉）
//    2. 车二进六 （将）  将6进1 （闲）
//    红方一捉一将，黑方一捉一闲，红方变着，不变作负。
// 📓 黑方退将后方可吃红兵，否则会被红方将死
TEST(MarkMove, Testx08)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_08);
    // b.show_board();

    moved = make_move("7973");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    // 退将避免吃后立即被将死
    moved = make_move("5859");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::PAWN);

    moved = make_move("7379");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("5958");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图 9 着法：
// 1. 马三退二（捉） 车９平８（捉）
// 2. 马二进三（兑） 车８平９（捉）
// 红方一捉一闲，黑方两捉，黑方变着，不变作负。
TEST(MarkMove, Testx09)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_09);
    // b.show_board();

    moved = make_move("6472");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    // 抽将吃子
    moved = make_move("8070");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7264");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    // 依旧可以将抽吃子
    moved = make_move("7080");
    b.DoMove(moved);

    // 标记杀耗时 17888ms
    // 不存在杀，而可反复将军时，非常耗时
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 图 10 着法：
// 1. 马七进六（捉） 车３进２（捉）
// 2. 马六退七（捉） 车３退２（捉）
// 红方进马、退马长捉黑车，黑方车一步捉无根
// 子，另一步为车炮联合捉子，红方变着，不变作负
// 📓 红退马后相方可吃车，否则会被将死
TEST(MarkMove, Testx10)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_10);
    // b.show_board();

    moved = make_move("2234");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    // 红方不能吃车，否则黑方一步杀
    moved = make_move("2624");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::HORSE);
    EXPECT_TRUE(moved.info.no_root_protected);

    moved = make_move("3422");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    moved = make_move("2426");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图 11 着法：
// 1. 炮八平九（捉） 车２平１（捉）
// 2. 炮九平八（捉） 车１平２（捉）
// 红方车炮联合捉子，黑方长捉无根子，黑方变着，不变作负
TEST(MarkMove, Testx11)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_11);
    // b.show_board();

    moved = make_move("1909");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ELEPHANT);
    EXPECT_TRUE(moved.info.is_jointed);

    moved = make_move("1808");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.no_root_protected);

    moved = make_move("0919");
    b.DoMove(moved);

    // 车炮联合捉象
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ELEPHANT);

    moved = make_move("0818");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 图 12 着法：
// 1. 车一平二（闲） 炮８平９（捉）
// 2. 车二平一（闲） 炮９平８（捉）
// 红方两闲，黑方两捉，黑方变着，不变作负。
TEST(MarkMove, Testx12)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_12);
    // b.show_board();

    moved = make_move("8676");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("7787");
    b.DoMove(moved);
    // 走子后可吃其他棋子
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.no_root_protected);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::PAWN);

    moved = make_move("7686");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("8777");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 图 13 着法：
// 1. 车五平六（将） 将４平５（闲）
// 2. 车六平五（兑） 将５平４（闲）
// 红方车五平六将军，造成黑方车 5 平 6 有杀，
// 属红方自毙。黑方进将为“闲”。红车平中路，判“兑”。
// 如黑方中炮无根，红方车六平五判“捉”。
// 红方一将一兑，黑方两闲，双方不变作和。
TEST(MarkMove, Testx13)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_13);
    // b.show_board();

    moved = make_move("4636");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("3949");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3646");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("4939");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 图14着法：
//    1.兵三平二 （闲）  车8平7 （捉）
//    2.兵二平三 （闲）  车7平8 （捉）
//    红方两着平兵捉车，按照兵（卒）本身允许长捉的规定，判闲。黑方两着动车，属长捉红方三路马。
//    红方两闲，黑方长捉。黑方变着，不变作负。
TEST(MarkMove, Testx14)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_14);
    // b.show_board();

    moved = make_move("6676");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("7767");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7666");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("6777");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 图 15 着法：
// 1. 帅六平五（捉） 卒５平４（闲）
// 2. 帅五平六（捉） 卒４平５（闲）
// 帅（将）允许长捉，但走动后，双马也轮流捉
// 卒，判“捉”。红方两捉，黑方两闲，红方变着，不变作负。
TEST(MarkMove, Testx15)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_15);
    // b.show_board();

    moved = make_move("3141");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4030");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("4131");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3040");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图 16 着法：
// 1. 车二进三（将） 将６进１（闲）
// 2. 车二退三（捉） 将６退１（捉）
// 红方一将一抽车，黑方将 6 退 1 避抽后，车可以吃兵，判“捉”。
// 红方一将一捉，黑方一闲一捉，红方变着，不变作负。
// 📓 退车可抽吃兵，同时将军，对手应将，继续吃掉黑车
TEST(MarkMove, Testx16)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_16);
    // b.show_board();

    moved = make_move("7679");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("5958");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("7976");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5859");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图 17 着法：
// 1. 后车进一（将） 将４进１（闲）
// 2. 后车退一（捉） 将４退１（杀）
// 红方后车退一，如黑方吃车则双车尽失，判“捉”。
// 黑方将 4 进 1，走动帅（将）应将后产生的“捉”、“杀”为“闲”。
// 红方一将一捉，黑方一闲一杀，红方变着，不变判负。
TEST(MarkMove, Testx17)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_17);

    moved = make_move("1718");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("3837");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("1817");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3738");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图 18 着法：
// 1. 车五平六（将） 将４平５（闲）
// 2. 车六平五（闲） 将５平４（杀）
// 红方一将一跟，占据守和要点，附带产生的捉象按“闲”着处理。
// 红方一将一闲，黑方一杀一闲，双方不变作和。
TEST(MarkMove, Testx18)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_18);
    // b.show_board();

    moved = make_move("4434");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("3949");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3444");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("4939");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 图 19 着法：
// 1. 车六平五（捉） 炮４平２（杀）
// 2. 车五平六（将） 炮２平４（杀）
// 红方一将一捉，黑炮平2是做杀，平4应将后增加了黑马退6的杀着。
// 红方一将一捉，黑方长杀，双方不变作和。
TEST(MarkMove, Testx19)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_19);
    // b.show_board();

    moved = make_move("3646");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3717");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("4636");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("1737");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 图 20 着法：
// 1. 马八进九（杀） 车３退２（闲）
// 2. 马九退八（捉） 车３进２（闲）
// 红马八进九兑车的同时，兼马九进七，马七退六再车九进二杀，即邀兑之子参与做杀，判杀；
// 马九退八判捉。红方一杀一捉，黑方两闲，红方变着，不变作负。
TEST(MarkMove, Testx20)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_20);
    // b.show_board();

    moved = make_move("1608");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("2628");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("0816");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2826");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图 21 着法：
// 1. 车四退二（兑） 炮２进２（捉）
// 2. 车四进二（捉） 炮２退２（捉）
// 红方一兑一捉，黑方长捉车，黑方变着，不变作负。
TEST(MarkMove, Testx21)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_21);
    // b.show_board();

    moved = make_move("5856");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("1816");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5658");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1618");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 图 22 着法：
// 1. 车六平五（捉） 卒５平４（闲）
// 2. 车五平六（捉） 卒４平５（闲）
// 红方两捉，黑方两闲，红方变着，不变作负。
TEST(MarkMove, Testx22)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_22);
    // b.show_board();

    moved = make_move("3646");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4434");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("4636");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3444");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图23着法：
//   1. 车七进一 （捉）  炮2进1 （闲）
//   2. 车七退一 （捉）  炮2退1 （闲）
//   红方进车、退车长捉黑炮；黑炮进退虽可打马、打相，但要丢车，被牵子捉子，交换结果得不偿失，判闲。
//   红方长捉，黑方两闲。红方变着，不变作负。
TEST(MarkMove, Testx23)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_23);
    // b.show_board();

    moved = make_move("2122");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1211");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("2221");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1112");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图 24
// 1. 车一进四（闲） 车５平６（闲）
// 2. 车一退四（捉） 车６平５（闲）
// 红方进车，可以送兵换马，兵卒价值浮动，判闲。
// 红方退车吃卒，将军后黑方垫车，红方可兵七平六将军弃兵得车，判捉。
// 红方一闲一捉，黑方两闲，双方不变作和。
TEST(MarkMove, Testx24)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_24);
    // b.show_board();

    moved = make_move("8589");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("4858");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("8985");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5848");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 图 25 着法：
// 1. 车六进一（捉） 马６退７（捉）
// 2. 车六退一（捉） 马７进６（捉）
// 红方联合捉子，黑方长捉车，黑方变着，不变作负。
TEST(MarkMove, Testx25)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_25);
    // b.show_board();

    moved = make_move("3435");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    moved = make_move("5567");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    moved = make_move("3534");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    moved = make_move("6755");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 图 26 着法：
// 1. 车六进三（捉） 炮８退３（捉）
// 2. 车六退三（捉） 炮８进３（捉）
// 红方一着捉无根子，一着捉少根子，黑方长捉车，黑方变着，不变作负。
// 红方一着捉无根子，一着捉少根子 无需变着
TEST(MarkMove, Testx26)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_26);
    // b.show_board();

    moved = make_move("3437");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7477");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    moved = make_move("3734");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    // 黑炮将军后可得红车
    moved = make_move("7774");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 图 27 着法：
// 1. 马八进七（捉） 炮１进１（捉）
// 2. 马七退八（捉） 炮１退１（捉）
// 红方长捉无根子，黑方车炮联合捉子，红方变着，不变作负
TEST(MarkMove, Testx27)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_27);
    // b.show_board();

    moved = make_move("1628");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.no_root_protected);

    moved = make_move("0908");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    moved = make_move("2816");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.no_root_protected);

    moved = make_move("0809");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 图 28 着法：
// 1. 车八平七（捉） 马３退５（捉）
// 2. 车七平八（捉） 马５进３（捉）
// 红方一着捉无根子，一着车炮联合捉子，黑方长捉车。黑方变着，不变作负。
// 如黑方马3退5改马3进5，也为黑方变着。
TEST(MarkMove, Testx28)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_28);
    // b.show_board();

    moved = make_move("1929");
    b.DoMove(moved);

    mark_move(b, moved);
    // 捉无根保护的马
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::HORSE);
    EXPECT_TRUE(moved.info.no_root_protected);

    moved = make_move("2748");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.no_root_protected);

    moved = make_move("2919");
    b.DoMove(moved);

    // 车炮联合捉士
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    moved = make_move("4827");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.no_root_protected);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 不能离线
// 图 29 着法：
// 1. 车一平二（兑） 车８平９（杀）
// 2. 车二平一（兑） 车９平７（杀）
// 3. 车一平三（兑） 车７平８（杀）
// 红方长兑，黑方长杀。黑方变着，不变作负。
// 本局红方首着如改走车五平二，因黑方8路车不能离线，判杀。
// 如续走车8平7，车二平三，车7平8，其结论即为：红方长杀，黑方长杀，双方不变作和。
TEST(MarkMove, Testx29x1)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_29);
    // b.show_board();

    moved = make_move("8373");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("7989");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("7383");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("8969");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("8363");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("6979");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    auto moves = b.get_last_moves(6);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 不能离线
// 图29 红方首着如改走车五平二，因黑方8路车不能离线，判杀。
// 如续走车8平7，车二平三，车7平8，其结论即为：红方长杀，黑方长杀，双方不变作和。
TEST(MarkMove, Testx29x2)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_29);
    // b.show_board();

    moved = make_move("4373");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("7969");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("7363");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("6979");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("6373");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("7969");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    auto moves = b.get_last_moves(6);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 图30着法：
//   1. 炮八退四 （捉）  车6退4 （兑）
//   2. 炮八进四 （兑）  车6进4 （捉）
//   红方一捉一兑，黑方一兑一捉，双方不变作和。
//   如黑方3路马改为7路对称位置，则黑方车6退4，判捉。红方一捉一闲，黑方长捉。黑方变着，不变作负。
TEST(MarkMove, Testx30x1)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_30);
    // b.show_board();

    moved = make_move("1612");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5256");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("1216");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("5652");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 黑方3路马改为7路对称位置，则黑方车6退4，判捉。红方一捉一闲，黑方长捉。黑方变着，不变作负。
TEST(MarkMove, Testx30x2)
{
    Board b;
    Move moved;
    b.set_pieces("2bakab2/9/4c1n1c/pCp1N3p/7n1/2P6/P3P1P1P/4CrN2/9/1RBAKAB2 w - - 0 1");
    // b.show_board();

    moved = make_move("1612");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5256");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1216");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5652");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}