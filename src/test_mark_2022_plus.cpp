#include <gtest/gtest.h>

#include "xqboard.hpp"
#include "test_cases.hpp"

// [==========] Running 50 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 50 tests from MarkMovePlus
// [ RUN      ] MarkMovePlus.Testx01
// [       OK ] MarkMovePlus.Testx01 (27 ms)
// [ RUN      ] MarkMovePlus.Testx02
// [       OK ] MarkMovePlus.Testx02 (125 ms)
// [ RUN      ] MarkMovePlus.Testx03
// [       OK ] MarkMovePlus.Testx03 (154 ms)
// [ RUN      ] MarkMovePlus.Testx04
// [       OK ] MarkMovePlus.Testx04 (87 ms)
// [ RUN      ] MarkMovePlus.Testx05
// [       OK ] MarkMovePlus.Testx05 (82 ms)
// [ RUN      ] MarkMovePlus.Testx06
// [       OK ] MarkMovePlus.Testx06 (105 ms)
// [ RUN      ] MarkMovePlus.Testx07
// [       OK ] MarkMovePlus.Testx07 (103 ms)
// [ RUN      ] MarkMovePlus.Testx08
// [       OK ] MarkMovePlus.Testx08 (352 ms)
// [ RUN      ] MarkMovePlus.Testx09
// [       OK ] MarkMovePlus.Testx09 (47 ms)
// [ RUN      ] MarkMovePlus.Testx10
// [       OK ] MarkMovePlus.Testx10 (84 ms)
// [ RUN      ] MarkMovePlus.Testx11
// [       OK ] MarkMovePlus.Testx11 (19 ms)
// [ RUN      ] MarkMovePlus.Testx12
// [       OK ] MarkMovePlus.Testx12 (1446 ms)
// [ RUN      ] MarkMovePlus.Testx13
// [       OK ] MarkMovePlus.Testx13 (64 ms)
// [ RUN      ] MarkMovePlus.Testx14
// [       OK ] MarkMovePlus.Testx14 (1291 ms)
// [ RUN      ] MarkMovePlus.Testx15
// [       OK ] MarkMovePlus.Testx15 (653 ms)
// [ RUN      ] MarkMovePlus.Testx16
// [       OK ] MarkMovePlus.Testx16 (50 ms)
// [ RUN      ] MarkMovePlus.Testx17
// [       OK ] MarkMovePlus.Testx17 (59 ms)
// [ RUN      ] MarkMovePlus.Testx18
// [       OK ] MarkMovePlus.Testx18 (129 ms)
// [ RUN      ] MarkMovePlus.Testx19
// [       OK ] MarkMovePlus.Testx19 (92 ms)
// [ RUN      ] MarkMovePlus.Testx20
// [       OK ] MarkMovePlus.Testx20 (532 ms)
// [ RUN      ] MarkMovePlus.Testx21
// [       OK ] MarkMovePlus.Testx21 (111 ms)
// [ RUN      ] MarkMovePlus.Testx22
// [       OK ] MarkMovePlus.Testx22 (30 ms)
// [ RUN      ] MarkMovePlus.Testx23
// [       OK ] MarkMovePlus.Testx23 (211 ms)
// [ RUN      ] MarkMovePlus.Testx24
// [       OK ] MarkMovePlus.Testx24 (109 ms)
// [ RUN      ] MarkMovePlus.Testx25
// [       OK ] MarkMovePlus.Testx25 (408 ms)
// [ RUN      ] MarkMovePlus.Testx26
// [       OK ] MarkMovePlus.Testx26 (67 ms)
// [ RUN      ] MarkMovePlus.Testx27
// [       OK ] MarkMovePlus.Testx27 (65 ms)
// [ RUN      ] MarkMovePlus.Testx28
// [       OK ] MarkMovePlus.Testx28 (122 ms)
// [ RUN      ] MarkMovePlus.Testx29
// [       OK ] MarkMovePlus.Testx29 (651 ms)
// [ RUN      ] MarkMovePlus.Testx30
// [       OK ] MarkMovePlus.Testx30 (149 ms)
// [ RUN      ] MarkMovePlus.Testx31
// [       OK ] MarkMovePlus.Testx31 (158 ms)
// [ RUN      ] MarkMovePlus.Testx32
// [       OK ] MarkMovePlus.Testx32 (350 ms)
// [ RUN      ] MarkMovePlus.Testx33
// [       OK ] MarkMovePlus.Testx33 (1301 ms)
// [ RUN      ] MarkMovePlus.Testx34
// [       OK ] MarkMovePlus.Testx34 (52 ms)
// [ RUN      ] MarkMovePlus.Testx35
// [       OK ] MarkMovePlus.Testx35 (116 ms)
// [ RUN      ] MarkMovePlus.Testx36
// [       OK ] MarkMovePlus.Testx36 (80 ms)
// [ RUN      ] MarkMovePlus.Testx37
// [       OK ] MarkMovePlus.Testx37 (45 ms)
// [ RUN      ] MarkMovePlus.Testx38
// [       OK ] MarkMovePlus.Testx38 (420 ms)
// [ RUN      ] MarkMovePlus.Testx39
// [       OK ] MarkMovePlus.Testx39 (33 ms)
// [ RUN      ] MarkMovePlus.Testx40
// [       OK ] MarkMovePlus.Testx40 (2522 ms)
// [ RUN      ] MarkMovePlus.Testx41
// [       OK ] MarkMovePlus.Testx41 (185 ms)
// [ RUN      ] MarkMovePlus.Testx42
// [       OK ] MarkMovePlus.Testx42 (1865 ms)
// [ RUN      ] MarkMovePlus.Testx43
// [       OK ] MarkMovePlus.Testx43 (122 ms)
// [ RUN      ] MarkMovePlus.Testx44
// [       OK ] MarkMovePlus.Testx44 (13 ms)
// [ RUN      ] MarkMovePlus.Testx45
// [       OK ] MarkMovePlus.Testx45 (21 ms)
// [ RUN      ] MarkMovePlus.Testx46
// [       OK ] MarkMovePlus.Testx46 (641 ms)
// [ RUN      ] MarkMovePlus.Testx47
// [       OK ] MarkMovePlus.Testx47 (108 ms)
// [ RUN      ] MarkMovePlus.Testx48
// [       OK ] MarkMovePlus.Testx48 (26 ms)
// [ RUN      ] MarkMovePlus.Testx49
// [       OK ] MarkMovePlus.Testx49 (67 ms)
// [ RUN      ] MarkMovePlus.Testx50
// [       OK ] MarkMovePlus.Testx50 (67 ms)
// [----------] 50 tests from MarkMovePlus (15644 ms total)

// [----------] Global test environment tear-down
// [==========] 50 tests from 1 test suite ran. (15644 ms total)
// [  PASSED  ] 50 tests.

// 参考图1着法:
//   1. 马二退四 （捉）   车7平6 （闲）
//   2. 马四进二 （捉）   车6平7 （闲）
//   红方马二退四伏前马进五吃象，判捉。
//   红方长捉，黑方两闲，红方变着，不变作负。
TEST(MarkMovePlus, Testx01)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_201);
    // b.show_board();

    moved = make_move("7554");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("6656");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5475");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5666");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图2着法：
//   1. 士四进五 （闲）  车7进1 （将）
//   2. 士五退四 （闲）  车7退1 （捉）
//   黑方车7退1，判捉。红方两闲，黑方一将一捉。黑方变着，不变作负。
TEST(MarkMovePlus, Testx02)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_202);
    // b.show_board();

    moved = make_move("5041");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("6160");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("4150");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("6061");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 参考图3着法：
//   1. 车四平五 （捉）  炮6平7 （闲）
//   2. 车五平四 （捉）  炮7平6 （捉）
//   红方两着平车，判捉。
//   红方长捉，黑方一闲一捉。红方变着，不变作负。
TEST(MarkMovePlus, Testx03)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_203);

    // b.show_board();

    moved = make_move("5343");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5868");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("4353");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("6858");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图4着法：
//   1. 炮八退一 （闲）  马3退1 （捉）
//   2. 炮八进一 （捉）  马1进3 （兑）
//   红方一闲一捉，黑方一捉一兑，双方不变作和。
TEST(MarkMovePlus, Testx04)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_204);
    // b.show_board();
    moved = make_move("1716");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("2708");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1617");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("0827");
    b.DoMove(moved);
    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图5着法：
//   1. 车九进三 （将）  后车退3 （兑）
//   2. 车九退一 （闲）  后车进1 （兑）
//   3. 车九退二 （闲）  后车进2 （兑）
//   黑方长兑，红方车九退一后，尽管下一着能兵二平三吃象，但兵（卒）本身允许长捉，吃象判闲。
//   红方一将两闲，黑方长兑，均为允许着法，双方不变作和。
TEST(MarkMovePlus, Testx05)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_205);
    // b.show_board();
    moved = make_move("0609");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("1619");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("0908");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("1918");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("0806");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("1816");
    b.DoMove(moved);
    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    auto moves = b.get_last_moves(6);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 典型案例 😋
// 参考图6着法：
//   1. 车九退二 （闲）  士4进5 （闲）
//   2. 车九进二 （将）  士5退4 （闲）
//   红方原本存在兵四进一吃士再车九平六吃士手段，车九退二后，白吃双士的结果没有发生变化，判闲。
//   红方一闲一将，黑方两闲，双方不变作和。
TEST(MarkMovePlus, Testx06)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_206);
    // b.show_board();
    moved = make_move("0907");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3948");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("0709");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("4839");
    b.DoMove(moved);

    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图7着法:
//   1.车二进三 （将） 将6进1 （闲）
//   2.车二退三 （闲） 将6退1 （闲）
//   红方一将一闲，黑方两闲，双方不变作和。
TEST(MarkMovePlus, Testx07)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_207);
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
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5859");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图8着法：
//   1.车七退一 （将） 将4退1 （闲）
//   2.车七进一 （将） 将4进1 （闲）
//   3.车七平一 （捉） 炮9平8 （捉）
//   4.车一平二 （捉） 炮8平9 （闲）
//   5.车二平一 （捉） 炮9平8 （捉）
//   6.车一平二 （捉） 炮8平9 （闲）
//   7.车二退六 （捉） 炮9进3 （将）
//   8.车二退三 （捉)  炮9退3 （闲）
//   9.车二进三 （捉） 炮9进3 （将）
//   红方均为禁止着法，须变着，不变作负。
TEST(MarkMovePlus, Testx08)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_208);
    // b.show_board();
    // 1
    moved = make_move("2928");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("3839");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    // 2
    moved = make_move("2829");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("3938");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    // 3
    moved = make_move("2989");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8373");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    // 4
    moved = make_move("8979");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7383");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    // 5
    moved = make_move("7989");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8373");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    // 6
    moved = make_move("8979");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7383");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    // 7
    moved = make_move("7973");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8380");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    // 8
    moved = make_move("7370");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8083");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    // 9
    moved = make_move("7073");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8380");
    b.DoMove(moved);
    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    auto moves = b.get_last_moves(18);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图9着法：
//   1.车三平二（兑）  车8平7 （闲）
//   2.车二平三（兑）  车7平8 （闲）
//   红方长兑，黑方两闲，双方不变作和。
TEST(MarkMovePlus, Testx09)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_209);
    // b.show_board();
    moved = make_move("6171");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("7262");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("7161");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("6272");
    b.DoMove(moved);

    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图10着法：
//   1.车五平四 （将） 士5进6 （闲）
//   2.车四平五 （捉） 士6退5 （杀）
//   红方一将一捉，黑方一闲一杀，红方变着，不变作负。
TEST(MarkMovePlus, Testx10)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_210);
    // b.show_board();

    moved = make_move("4656");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("4857");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5646");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5748");
    b.DoMove(moved);

    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 典型案例
// 参考图11着法：
//   1.帅五平四 （闲)   炮5平6（捉）
//   2.帅四平五 （闲）  炮6平5 (闲）
//   黑方炮5平6为炮卒联合捉子，炮6平5卒捉仕，判闲。
//   红方两闲，黑方一捉一闲，双方不变作和。
TEST(MarkMovePlus, Testx11)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_211);
    // b.show_board();

    moved = make_move("4050");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("4454");
    b.DoMove(moved);

    // 平炮后联合卒捉士
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5040");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5444");
    b.DoMove(moved);

    // 非将军得子，兵、卒允许长捉
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图12着法：
//    1.车八平六 （将） 将4平5 （闲）
//    2.车六平八 （捉） 将5平4 （捉）
//    红方一将一捉，黑方一闲一捉。红方变着，不变作负
TEST(MarkMovePlus, Testx12)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_212);
    // b.show_board();

    moved = make_move("1131");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("3949");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3111");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4939");
    b.DoMove(moved);
    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图13着法：
//   1. 炮八平六（闲） 车2平4 （捉）
//   2. 炮六平八（闲） 车4平2 （捉）
//   黑方车2平4，伏炮打仕，白得红仕，判捉。红方两闲，黑方长捉。黑方变着，不变作负。
TEST(MarkMovePlus, Testx13)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_213);
    // b.show_board();

    moved = make_move("1232");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("1333");
    b.DoMove(moved);

    // 炮打士得士
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3212");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3313");
    b.DoMove(moved);

    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 参考图14着法:
//   1.马一退三 （捉） 车9平8 （捉）
//   2.马三进一 （捉） 车8平9 （捉）
//   红方长捉车，黑方为车炮联合捉车。红方变着，不变作负。
TEST(MarkMovePlus, Testx14)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_214);
    // b.show_board();

    moved = make_move("8261");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8070");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);
    EXPECT_EQ(moved.info.zhuo_tgt.piece, PieceType::ROOK);

    moved = make_move("6182");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7080");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图15着法：
//   1.炮六退二 （捉） 车8退2  （捉）
//   2.炮六进二 （闲） 车8进2  （闲）
//   双方均为一捉一闲，双方不变作和。
TEST(MarkMovePlus, Testx15)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_215);
    // b.show_board();

    moved = make_move("3331");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7173");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3133");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("7371");
    b.DoMove(moved);

    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图16着法：
//   1.兵五平六 （捉） 车5平4 （闲）
//   2.兵六平五 （捉） 车4平5 （闲）
//   红方长捉，黑方两闲。红方变着，不变作负。
TEST(MarkMovePlus, Testx16)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_216);
    // b.show_board();

    moved = make_move("4636");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4535");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3646");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3545");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图17着法:
//   1.车六进四 （将）  将5退1 （闲）
//   2.车六退四 （闲）  将5进1 （捉）
//   红方一将一闲，黑方一闲一捉，双方不变作和。
TEST(MarkMovePlus, Testx17)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_217);
    // b.show_board();

    moved = make_move("3438");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("4849");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3834");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("4948");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图18着法:
//   1.帅五平六 （捉）  车2平4 （将）
//   2.帅六平五 （闲）  车4平2 （捉）
//   红方帅五平六，车捉马，判捉；黑方车2平4，判将，红帅六平五应将，判闲。黑方车4平2伏抽车，判捉。
//   红方一捉一闲，黑方一将一捉，黑方变着，不变作负。
TEST(MarkMovePlus, Testx18)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_218);
    // b.show_board();

    moved = make_move("4030");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1232");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("3040");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3212");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 参考图19着法：
//   1.车三平五 （将） 士6进5 （闲）
//   2.车五平三 （捉） 士5退6 （闲）
//   红方一将一捉，黑方两闲。红方变着，不变作负。
TEST(MarkMovePlus, Testx19)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_219);
    // b.show_board();

    moved = make_move("6343");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("5948");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("4363");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4859");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 典型案例
// 参考图20着法：
//   1.帅五退一 （捉） 车3进8 （将）
//   2.帅五进一 （闲） 车3退8 （捉）
//   黑方车3进8将军，红方上帅后，刚产生黑方炮8平1打车，但由于红方有马七退八的杀着，故车3退8解杀后才形成了实际的捉。
//   红方帅五退一，九路车捉炮判捉，帅五进一判闲。
//   红方一捉一闲，黑方一将一捉。黑方变着，不变作负。
TEST(MarkMovePlus, Testx20)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_220);
    // b.show_board();

    moved = make_move("4140");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2820");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("4041");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("2028");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 参考图21着法：
//   1.马七进八 （捉）  车4退1 （捉）
//   2.马八退七 （捉）  车4进1 （闲）
//   黑方车4进1后，红方三路线上黑车与红马并没有参与循环着法，红马被黑车捉的状态，其因果关系，
//   是红方自己造成的，判闲。 红方长捉，黑方一捉一闲。红方变着，不变判负。
TEST(MarkMovePlus, Testx21)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_221);
    // b.show_board();

    moved = make_move("2214");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3334");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1422");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3433");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图22着法：
//   1. 车四平五 （兑）  炮6平2 （杀）
//   2. 车五平四 （将）  炮2平6 （闲）
//   红方车五平四将军，使红炮失去保护，是自己造成的被捉状态，黑方炮2平6判闲。
//   红方一将一兑，黑方一杀一闲，双方不变作和。
TEST(MarkMovePlus, Testx22)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_222);
    // b.show_board();

    moved = make_move("5444");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    moved = make_move("5717");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("4454");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("1757");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图23着法：
//   1.炮六进二 （捉）  炮3进4 （闲）
//   2.炮六退二 （捉）  炮3退4 （捉）
//   红方炮六退二为献兼捉，从重判捉。红方长捉，黑方一闲一捉。红方变着，不变作负。
TEST(MarkMovePlus, Testx23)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_223);
    // b.show_board();

    moved = make_move("3638");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2925");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3836");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2529");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图24着法:
//   1. 炮一平三 （捉） 象7退9 （闲）
//   2. 炮三平一 （捉） 象9进7 （闲）
//   红方炮一平三为献兼捉，从重判捉。 红方长捉，黑方两闲。红方变着，不变作负。
TEST(MarkMovePlus, Testx24)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_224);
    // b.show_board();

    moved = make_move("8262");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("6587");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("6282");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8765");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图25着法：
//   1.炮五平四（将）将6平5（闲）
//   2.炮四平五（捉）将5平6（闲）
//   红方炮四平五，伏车五进三吃炮，判捉。红方一将一捉，黑方两闲。红方变着，不变作负。
TEST(MarkMovePlus, Testx25)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_225);
    // b.show_board();

    moved = make_move("4252");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("5949");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5242");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4959");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图26着法：
//   1.马三进二（捉） 车5退1 （闲）
//   2.马二退三（捉） 车5进1 （闲）
//   红方进马兑兼捉，从重判“捉”。红方长捉，黑方两闲。红方变着，不变作负。
TEST(MarkMovePlus, Testx26)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_226);
    // b.show_board();

    moved = make_move("6678");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4647");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("7866");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4746");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图27着法：
//   1.炮六平七（捉）车3平4（闲）
//   2.炮七平六（捉）车4平3（闲）
//   红方长捉，黑方两闲，红方变着，不变作负
TEST(MarkMovePlus, Testx27)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_227);
    // b.show_board();

    moved = make_move("3626");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2131");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("2636");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3121");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图28着法：
//   1.车二平四（将）士5进6（闲）
//   2.车四平二（闲）士6退5（捉）
//   红方车四平二是做根子捉子，得不偿失，判闲；黑方退士断根捉马，判捉。
//   红方一将一闲，黑方一闲一捉，双方不变作和。
TEST(MarkMovePlus, Testx28)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_228);
    // b.show_board();

    moved = make_move("7252");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("4857");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5272");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5748");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 考图29着法：
//   1.帅五退一（闲）车6进3（将）
//   2.帅五进一（闲）车6退3（捉）
//   黑方车6退3，伏弃卒将军换车，判捉。红方两闲，黑方一将一捉，黑方变着，不变作负。
TEST(MarkMovePlus, Testx29)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_229);
    // b.show_board();

    moved = make_move("4140");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5350");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("4041");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5053");
    b.DoMove(moved);

    // b.show_board();
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 参考图30着法：
//   1.车四平三（杀） 将5平6（闲）
//   2.车三平四（捉） 将6平5（闲）
//   红方车三平四，伏平兵将军抽吃马，判捉。 红方一杀一捉，黑方两闲。红方变着，不变作负。
TEST(MarkMovePlus, Testx30)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_230);
    // b.show_board();

    moved = make_move("5969");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("4757");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("6959");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5747");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 原图存在错误，已经修正
// 参考图31着法：
//   1.炮五退二 （闲）  象9进7 （闲）
//   2.炮五进二 （闲）  象7退9 （闲）
//   黑方象9进7，欲3路炮打兵，但打兵后，红方可炮五进四打象，然后再马三进一吃炮，以浮动价值的兵交换象，判闲。
//   红方两闲，黑方两闲，双方不变作和。
TEST(MarkMovePlus, Testx31)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_231);
    // b.show_board();

    moved = make_move("4543");
    b.DoMove(moved);
    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("8765");
    b.DoMove(moved);
    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("4345");
    b.DoMove(moved);
    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("6587");
    b.DoMove(moved);
    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图32着法：
//   1.马三进二 (闲)   炮6进1 （闲）
//   2.马二退三 (捉）  炮6退1 （闲）
//   红方马三进二欲交换炮后帅吃马，先等值交换后，帅才能吃马，帅并没有与其他子同时捉马，判闲。
//   红方一闲一捉，黑方两闲。双方不变作和。
TEST(MarkMovePlus, Testx32)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_232);
    // b.show_board();

    moved = make_move("6678");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("5958");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("7866");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5859");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图33着法：
//   1.马八退七 （捉）  炮4退1 （闲）
//   2.马七进八 （闲）  炮4进1 （闲） 应为捉：将军可得士
//   黑方进炮退炮均为闲。红方退马判捉，进马后如兵先吃士，则浮动价值的兵换士、炮为等值交换，判闲；
//   又如马先吃炮，黒士吃马，等值交换后兵吃士，判闲。红方一捉一闲，黑方两闲，双方不变作和。
TEST(MarkMovePlus, Testx33)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_233);
    // b.show_board();

    moved = make_move("1826");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3839");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("2618");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("3938");
    b.DoMove(moved);

    // b.show_board();
    mark_move(b, moved);
    // 原文标记为闲，实际可将军得士
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图34着法：
//   1. 车二退六 （捉）  炮9退2 （捉）
//   2. 车二进六 （捉）  炮9进2 （杀）
//   红方长捉无根子，黑方一联合捉子一杀。红方变着，不变作负。
TEST(MarkMovePlus, Testx34)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_234);
    // b.show_board();

    moved = make_move("7670");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    moved = make_move("8082");
    b.DoMove(moved);

    // 红方如吃炮，黑方将军得车
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7076");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8280");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图35着法：
//   1.马四退六 （捉）  车6平4 （捉）
//   2.马六进四 （杀）  车4平6 （捉）
//   红方退马捉黑方车、炮，进马为杀。黑方车6平4捉红马，车4平6解杀后形成炮捉车，判捉。
//   红方一捉车一杀，黑方一捉无根子一捉车，双方不变作和。
TEST(MarkMovePlus, Testx35)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_235);
    // b.show_board();

    moved = make_move("5635");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5434");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3556");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("3454");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 典型案例 😋
// 参考图36着法：
//   1. 马九退七 （捉）  车1平2 （捉）
//   2. 马七进九 （捉）  车2平1 （捉）
//   红方一捉车一捉无根子，黑方长捉少根子。红方变着，不变作负。
TEST(MarkMovePlus, Testx36)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_236);
    // b.show_board();

    moved = make_move("0221");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("0010");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2102");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1000");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 典型案例：黑避吃促成得子，但没有加强进攻子力，判闲
// 参考图37着法：
//   1.车三退一 （捉）  炮9退1 （闲）
//   2.车三进一 （捉）  炮9进1 （闲）
//   红方长捉，黑方两闲。红方变着，不变作负。
TEST(MarkMovePlus, Testx37)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_237);
    // b.show_board();

    moved = make_move("6564");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8485");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    moved = make_move("6465");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8584");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::XIAN);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图38着法：
//   1.马一进三 （捉） 车8平7 （捉）
//   2.马三退一 （捉） 车7平8 （捉）
//   红方长捉车，黑方联合捉车，红方变着，不变作负。
TEST(MarkMovePlus, Testx38)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_238);
    // b.show_board();

    moved = make_move("8162");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.no_root_protected);
    EXPECT_FALSE(moved.info.is_jointed);

    moved = make_move("7060");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    moved = make_move("6281");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.no_root_protected);
    EXPECT_FALSE(moved.info.is_jointed);

    moved = make_move("6070");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_TRUE(moved.info.is_jointed);

    // 红方长捉无根子，黑方联合捉车，红方不变判负
    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 不能离线
// 参考图39着法：
//   1.车三退一 （捉）  马5进6 （捉）
//   2.车三进一 （捉）  马6退5 （捉）
//   红方车马炮联合联合捉车，黑方长捉车。黑方变着，不变作负。
TEST(MarkMovePlus, Testx39)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_239);
    // b.show_board();

    moved = make_move("6766");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4654");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("6667");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5446");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// ⚠️ 标注杀耗时
// 参考图40着法：
//   1.马八退七 （捉）  炮4进1 （捉）
//   2.马七进八 （捉）  炮4退1 （捉）
//   红方长捉无根子，黑方马炮联合捉子，红方变着，不变作负。
TEST(MarkMovePlus, Testx40)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_240);
    // b.show_board();

    moved = make_move("1826");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3837");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2618");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3738");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图41着法：
//   1.炮二平六 （捉） 车8平4 （捉）
//   2.炮六平二 （捉） 车4平8 （捉）
//   红方炮二平六捉无根象，炮六平二为联合捉子，黑方长捉无根子。黑方变着，不变作负。
TEST(MarkMovePlus, Testx41)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_241);
    // b.show_board();

    moved = make_move("7838");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7333");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3878");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("3373");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 1);
}

// 参考图42着法：
//   1.仕五退六 （捉）  炮3进7 （将）
//   2.仕六进五 （杀）  炮3退7  (捉）
//   红方一联合捉子一杀，黑方一将一联合捉子，双方不变作和。
TEST(MarkMovePlus, Testx42)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_242);
    // b.show_board();

    moved = make_move("4130");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2720");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("3041");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("2027");
    b.DoMove(moved);

    // 移动前并不能互吃得士，如黑炮吃士，则反被红杀
    // 将军捉士
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图例43着法：
//   1. 车五平八 （捉） 炮2平5 （杀）
//   2. 车八平五 （捉） 炮5平2 （杀）
//   红方长捉无根子，黑方长杀，双方不变作和。
TEST(MarkMovePlus, Testx43)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_243);
    // b.show_board();

    moved = make_move("4313");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1545");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    moved = make_move("1343");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4515");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图44着法：
//   1.车四平一 （捉）  炮6平9 （捉）
//   2.车一平四 （捉）  炮9平6 （捉）
//   红方长无根子，黑方长捉车，双方不变作和。
TEST(MarkMovePlus, Testx44)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_244);
    // b.show_board();

    moved = make_move("5686");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5181");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8656");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8151");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

//  参考图45着法：
//    1.炮三平一 （捉）  马9进7 （捉）
//    2.炮一平三 （捉）  马7退9 （捉）
//    红方一捉车一捉无根象，黑方长捉无根炮，双方不变作和。
TEST(MarkMovePlus, Testx45)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_245);
    // b.show_board();

    moved = make_move("6989");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8867");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8969");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("6788");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

//  参考图46着法：
//    1. 车二平一 （捉）   马9进7 （捉）
//    2. 车一平二 （捉）   马7退9 （捉）
//    红方长捉无根子，黑方长捉车，双方不变作和。
TEST(MarkMovePlus, Testx46)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_246);
    // b.show_board();

    moved = make_move("7686");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8867");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("8676");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("6788");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图47着法:
//   1. 炮五平三 （捉） 后炮平5 （将）
//   2. 炮三平五 （捉）  炮5平7  (捉）
//   红方长捉无根子，黑方一将一捉车，双方不变作和。
TEST(MarkMovePlus, Testx47)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_247);
    // b.show_board();

    moved = make_move("4262");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("6545");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("6242");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("4565");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 参考图48着法：
//   1.车二退一 （捉） 士6进5 （捉）
//   2.车二进一 （将） 士5退6 （杀）
//   红方一捉无根子一将，黑方一捉车一杀，双方不变作和。
TEST(MarkMovePlus, Testx48)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_248);
    // b.show_board();

    moved = make_move("7978");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("5948");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("7879");
    b.DoMove(moved);
    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::JIANG);

    moved = make_move("4859");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::SHA);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, 0);
}

// 不能离线
// 参考图49着法：
//   1.马八进七 （捉）  车2平3 （捉）
//   2.马七退八 （捉）  车3平2 （捉）
//   红方进马退马均使黑方四路炮不能离线，为长捉无根子；黑方一着捉无根子，一着捉少根子。红方变着，不变作负
TEST(MarkMovePlus, Testx49)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_249);
    // b.show_board();

    moved = make_move("1628");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1525");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2816");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2515");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);
    EXPECT_EQ(moved.info.no_root_protected, false);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

// 参考图50着法：
//   1. 马八进七 （捉） 车2平3 （捉）
//   2. 马七退八 （捉） 车3平2  (兑）
//   红方长捉，黑方一捉一兑。红方变着，不变作负。
TEST(MarkMovePlus, Testx50)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_250);
    // b.show_board();

    moved = make_move("1628");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("1525");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2816");
    b.DoMove(moved);

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::ZHUO);

    moved = make_move("2515");
    b.DoMove(moved);

    // b.show_board();

    mark_move(b, moved);
    EXPECT_EQ(moved.info.move_t, MoveType::DUI);

    auto moves = b.get_last_moves(4);
    auto result = adjudicate(moves, S_RED);
    EXPECT_EQ(result, -1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}