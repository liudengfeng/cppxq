#include <gtest/gtest.h>

#include "common.hpp"
#include "board.hpp"
#include "test_cases.hpp"

// [==========] Running 51 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 51 tests from BoardBasicTest
// [ RUN      ] BoardBasicTest.Runx01x1
// [       OK ] BoardBasicTest.Runx01x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx01x2
// [       OK ] BoardBasicTest.Runx01x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx01x3
// [       OK ] BoardBasicTest.Runx01x3 (1 ms)
// [ RUN      ] BoardBasicTest.Runx02x1
// [       OK ] BoardBasicTest.Runx02x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx02x2
// [       OK ] BoardBasicTest.Runx02x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx03x1
// [       OK ] BoardBasicTest.Runx03x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx03x2
// [       OK ] BoardBasicTest.Runx03x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx03x3
// [       OK ] BoardBasicTest.Runx03x3 (0 ms)
// [ RUN      ] BoardBasicTest.Runx03x4
// [       OK ] BoardBasicTest.Runx03x4 (0 ms)
// [ RUN      ] BoardBasicTest.Runx03x5
// [       OK ] BoardBasicTest.Runx03x5 (0 ms)
// [ RUN      ] BoardBasicTest.Runx04x1
// [       OK ] BoardBasicTest.Runx04x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx04x2
// [       OK ] BoardBasicTest.Runx04x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx04x3
// [       OK ] BoardBasicTest.Runx04x3 (0 ms)
// [ RUN      ] BoardBasicTest.Runx05x1
// [       OK ] BoardBasicTest.Runx05x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx05x2
// [       OK ] BoardBasicTest.Runx05x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx06x1
// [       OK ] BoardBasicTest.Runx06x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx06x2
// [       OK ] BoardBasicTest.Runx06x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx07x1
// [       OK ] BoardBasicTest.Runx07x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx07x2
// [       OK ] BoardBasicTest.Runx07x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx08x1
// [       OK ] BoardBasicTest.Runx08x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx08x2
// [       OK ] BoardBasicTest.Runx08x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx09x1
// [       OK ] BoardBasicTest.Runx09x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx09x2
// [       OK ] BoardBasicTest.Runx09x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx09x3
// [       OK ] BoardBasicTest.Runx09x3 (0 ms)
// [ RUN      ] BoardBasicTest.Runx09x4
// [       OK ] BoardBasicTest.Runx09x4 (0 ms)
// [ RUN      ] BoardBasicTest.Runx09x5
// [       OK ] BoardBasicTest.Runx09x5 (0 ms)
// [ RUN      ] BoardBasicTest.Runx09x6
// [       OK ] BoardBasicTest.Runx09x6 (0 ms)
// [ RUN      ] BoardBasicTest.Runx09x7
// [       OK ] BoardBasicTest.Runx09x7 (0 ms)
// [ RUN      ] BoardBasicTest.Runx10x1
// [       OK ] BoardBasicTest.Runx10x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx10x2
// [       OK ] BoardBasicTest.Runx10x2 (1 ms)
// [ RUN      ] BoardBasicTest.Runx10x3
// [       OK ] BoardBasicTest.Runx10x3 (0 ms)
// [ RUN      ] BoardBasicTest.Runx10x4
// [       OK ] BoardBasicTest.Runx10x4 (0 ms)
// [ RUN      ] BoardBasicTest.Runx11x1
// [       OK ] BoardBasicTest.Runx11x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx11x2
// [       OK ] BoardBasicTest.Runx11x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx11x3
// [       OK ] BoardBasicTest.Runx11x3 (0 ms)
// [ RUN      ] BoardBasicTest.Runx11x4
// [       OK ] BoardBasicTest.Runx11x4 (1 ms)
// [ RUN      ] BoardBasicTest.Runx11x5
// [       OK ] BoardBasicTest.Runx11x5 (0 ms)
// [ RUN      ] BoardBasicTest.Runx11x6
// [       OK ] BoardBasicTest.Runx11x6 (0 ms)
// [ RUN      ] BoardBasicTest.Runx11x8
// [       OK ] BoardBasicTest.Runx11x8 (0 ms)
// [ RUN      ] BoardBasicTest.Runx11x9
// [       OK ] BoardBasicTest.Runx11x9 (0 ms)
// [ RUN      ] BoardBasicTest.Runx12x1
// [       OK ] BoardBasicTest.Runx12x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx12x2
// [       OK ] BoardBasicTest.Runx12x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx12x3
// [       OK ] BoardBasicTest.Runx12x3 (0 ms)
// [ RUN      ] BoardBasicTest.Runx13x1
// [       OK ] BoardBasicTest.Runx13x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx13x2
// [       OK ] BoardBasicTest.Runx13x2 (1 ms)
// [ RUN      ] BoardBasicTest.Runx14x1
// [       OK ] BoardBasicTest.Runx14x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx14x2
// [       OK ] BoardBasicTest.Runx14x2 (0 ms)
// [ RUN      ] BoardBasicTest.Runx14x3
// [       OK ] BoardBasicTest.Runx14x3 (0 ms)
// [ RUN      ] BoardBasicTest.Runx14x4
// [       OK ] BoardBasicTest.Runx14x4 (0 ms)
// [ RUN      ] BoardBasicTest.Runx15x1
// [       OK ] BoardBasicTest.Runx15x1 (0 ms)
// [ RUN      ] BoardBasicTest.Runx16x1
// [       OK ] BoardBasicTest.Runx16x1 (0 ms)
// [----------] 51 tests from BoardBasicTest (15 ms total)

// [----------] Global test environment tear-down
// [==========] 51 tests from 1 test suite ran. (15 ms total)
// [  PASSED  ] 51 tests.

TEST(BoardBasicTest, Runx01x1)
{
    // 默认99，非法位置
    Coord c1;
    EXPECT_EQ(c1.toString(), "99");
    EXPECT_EQ(c1.x, 9);
    EXPECT_EQ(c1.y, 9);
    EXPECT_TRUE(c1.off_board());
    EXPECT_FALSE(c1.on_board());

    // 第一位代表x轴坐标、第二位代表y轴坐标
    Coord c2{0, 1};
    EXPECT_EQ(c2.toString(), "01");
    EXPECT_EQ(c2.id(), 9);

    Coord c3{9};
    EXPECT_EQ(c2, c3);
    EXPECT_EQ(c3.x, 0);
    EXPECT_EQ(c3.y, 1);

    // 恰好相等
    Coord c4{8, 9};
    EXPECT_EQ(c4.id(), 89);

    for (size_t i = 0; i < 90; i++)
    {
        auto c = Coord(i);
        auto x = i % BOARD_WIDTH;
        auto y = i / BOARD_WIDTH;
        EXPECT_EQ(c.id(), i);
        EXPECT_EQ(c.x, x);
        EXPECT_EQ(c.y, y);
    }

    for (size_t x = 0; x < BOARD_WIDTH; x++)
    {
        for (size_t y = 0; y < BOARD_HEIGHT; y++)
        {
            auto c = Coord(x, y);
            EXPECT_EQ(c.id(), y * BOARD_WIDTH + x);
            EXPECT_EQ(c.x, x);
            EXPECT_EQ(c.y, y);
        }
    }
}

TEST(BoardBasicTest, Runx01x2)
{
    auto m1 = make_move("0001");
    auto m2 = make_move("0102");
    EXPECT_LT(m1, m2);

    auto m3 = make_move("2328");
    auto m4 = make_move("2926");
    EXPECT_LT(m3, m4);
}

// 连续未吃子计数
TEST(BoardBasicTest, Runx01x3)
{
    Board b;
    auto move1 = make_move("0001");
    auto move2 = make_move("8987");
    auto move3 = make_move("0131");
    b.DoMove(move1);
    b.DoMove(move2);
    b.DoMove(move3);
    EXPECT_EQ(b.no_eat(), 3);

    auto move4 = make_move("1710");
    b.DoMove(move4);
    EXPECT_EQ(b.no_eat(), 0);

    b.undoNSteps(1);
    EXPECT_EQ(b.no_eat(), 3);

    b.undoNSteps(2);
    EXPECT_EQ(b.no_eat(), 1);
}

TEST(BoardBasicTest, Runx01x4)
{
    Board b;
    b.set_pieces("2bak1c2/4aRN1r/4b4/9/9/9/3pp4/2n1B4/9/2B1K3C w - 119 0 1");
}

TEST(BoardBasicTest, Runx02x1)
{
    Board b;
    auto m = make_move("2042");
    b.DoMove(m);
    EXPECT_EQ(b.next_player(), S_BLACK);

    b.SetPlayer(S_RED);
    EXPECT_EQ(b.next_player(), S_RED);
}

TEST(BoardBasicTest, Runx02x2)
{
    // w 为红方
    Board b;
    b.set_pieces("3ak4/3P5/R4a3/9/4N4/6n2/6r2/5p3/4p4/5K3 w - - 0 1");
    EXPECT_EQ(b.next_player(), S_RED);

    b.set_pieces("3ak4/3P5/R4a3/9/4N4/6n2/6r2/5p3/4p4/5K3 b - - 0 1");
    EXPECT_EQ(b.next_player(), S_BLACK);
}

// 验证设置棋子

// 将、帅位置、数量
TEST(BoardBasicTest, Runx03x1)
{
    Board b;
    std::string fen_ok = "r1b1kab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA1r1 w - - 0 1";
    std::string fen_wrong = "r1b1kab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R1K3/1cBAKA1r1 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

TEST(BoardBasicTest, Runx03x2)
{
    Board b;
    std::string fen_ok = "r1b1kab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA1r1 w - - 0 1";
    std::string fen_wrong = "r1b1kab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P2K2P/2c1C2N1/3R5/1cBA1A1r1 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

TEST(BoardBasicTest, Runx03x3)
{
    Board b;
    std::string fen_ok = "r1b1kab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA1r1 w - - 0 1";
    std::string fen_wrong = "r1b2ab2/4a4/2n6/p3pk1Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA1r1 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

// 黑方2个将
TEST(BoardBasicTest, Runx03x4)
{
    Board b;
    std::string fen_ok = "r1b1kab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA1r1 w - - 0 1";
    std::string fen_wrong = "r1bkkab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA1r1 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

// 黑方缺将
TEST(BoardBasicTest, Runx03x5)
{
    Board b;
    std::string fen_ok = "r1b1kab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA1r1 w - - 0 1";
    std::string fen_wrong = "r1b2ab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA1r1 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

// 士
TEST(BoardBasicTest, Runx04x1)
{
    Board b;
    std::string fen_wrong_1 = "r1bakab2/9/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R1A3/1cBAK4 w - - 0 1";
    std::string fen_wrong_2 = "r1b1kab2/9/2n1a4/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA3 w - - 0 1";

    EXPECT_THROW(b.set_pieces(fen_wrong_1, true), std::out_of_range);
    EXPECT_THROW(b.set_pieces(fen_wrong_2, true), std::out_of_range);
}

TEST(BoardBasicTest, Runx04x2)
{
    Board b;
    std::string fen_wrong_1 = "r1bakab2/9/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3RA4/1cBAKA3 w - - 0 1";
    std::string fen_wrong_2 = "r1bakab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/1cBAKA3 w - - 0 1";

    EXPECT_THROW(b.set_pieces(fen_wrong_1, true), std::out_of_range);
    EXPECT_THROW(b.set_pieces(fen_wrong_2, true), std::out_of_range);
}

// 缺士
TEST(BoardBasicTest, Runx04x3)
{
    Board b;
    std::string fen_1 = "r1bakab2/9/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/2B1K4 w - - 0 1";
    std::string fen_2 = "r1b1k1b2/9/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/2B1K4 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_1, true));
    EXPECT_NO_THROW(b.set_pieces(fen_2, true));
}

// 象
TEST(BoardBasicTest, Runx05x1)
{
    Board b;
    std::string fen_wrong_1 = "r1b1k1b2/9/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/1B1R5/4K4 w - - 0 1";
    std::string fen_wrong_2 = "r1b1k1b2/9/2n6/p3p2Rp/2p1P4/6B2/P1P5P/2c1C2N1/3R5/2B1K1B2 w - - 0 1";

    EXPECT_THROW(b.set_pieces(fen_wrong_1, true), std::out_of_range);
    EXPECT_THROW(b.set_pieces(fen_wrong_2, true), std::out_of_range);
}

TEST(BoardBasicTest, Runx05x2)
{
    Board b;
    std::string fen_wrong_1 = "r1b1k1b2/9/2n6/p3pb1Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/2B1K1B2 w - - 0 1";
    std::string fen_wrong_2 = "r3k1b2/1b7/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/2B1K1B2 w - - 0 1";

    EXPECT_THROW(b.set_pieces(fen_wrong_1, true), std::out_of_range);
    EXPECT_THROW(b.set_pieces(fen_wrong_2, true), std::out_of_range);
}

// 马
TEST(BoardBasicTest, Runx06x1)
{
    Board b;
    std::string fen_ok = "r3k1b2/9/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/2B1K1B2 w - - 0 1";
    std::string fen_wrong = "r3k1b2/9/2n6/p3p2Rp/2p1P4/5nn2/P1P5P/2c1C2N1/3R5/2B1K1B2 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

TEST(BoardBasicTest, Runx06x2)
{
    Board b;
    std::string fen_ok = "r3k1b2/9/2n6/p3p2Rp/2p1P4/9/P1P5P/2c1C2N1/3R5/2B1K1B2 w - - 0 1";
    std::string fen_wrong = "r3k1b2/9/2n6/p3p2Rp/2p1P1NN1/9/P1P5P/2c1C2N1/3R5/2B1K1B2 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

// 炮
TEST(BoardBasicTest, Runx07x1)
{
    Board b;
    std::string fen_ok = "r3k1b2/9/2n6/p3p2Rp/2p1P2N1/9/P1P5P/2c4N1/3R5/2B1K1B2 w - - 0 1";
    std::string fen_wrong = "r3k1b2/9/2n6/p3p2Rp/2p1P2N1/4CC3/P1P1C3P/2c4N1/3R5/2B1K1B2 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

TEST(BoardBasicTest, Runx07x2)
{
    Board b;
    std::string fen_ok = "r3k1b2/9/2n6/p3p2Rp/2p1P2N1/9/P1P5P/2c4N1/3R5/2B1K1B2 w - - 0 1";
    std::string fen_wrong = "r3k1b2/9/2n6/p3p2Rp/2p1P2N1/4C4/P1P5P/2ccc2N1/3R5/2B1K1B2 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

// 车
TEST(BoardBasicTest, Runx08x1)
{
    Board b;
    std::string fen_ok = "r3k1b2/9/2n6/p3p3p/2p1P2N1/4C4/P1P5P/2cc3N1/9/2B1K1B2 w - - 0 1";
    std::string fen_wrong = "r3k1b2/9/2n6/p3pR2p/2p1PR1N1/4CR3/P1P5P/2cc3N1/9/2B1K1B2 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

TEST(BoardBasicTest, Runx08x2)
{
    Board b;
    std::string fen_ok = "r3k1b2/9/2n6/p3p3p/2p1P2N1/4C4/P1P5P/2cc3N1/9/2B1K1B2 w - - 0 1";
    std::string fen_wrong = "r3k1b2/9/2n6/p3pr2p/2p1Pr1N1/4Cr3/P1P5P/2cc3N1/9/2B1K1B2 w - - 0 1";

    EXPECT_NO_THROW(b.set_pieces(fen_ok));
    EXPECT_NO_THROW(b.set_pieces(fen_wrong, false));
    EXPECT_THROW(b.set_pieces(fen_wrong, true), std::out_of_range);
}

// 候选

// 将、帅
TEST(BoardBasicTest, Runx09x1)
{
    moveVec_t cands0, cands;
    Board b;
    b.set_pieces("r4kb2/9/2n6/p3p3p/2p1P2N1/4C4/P1P5P/2cc3N1/9/2B1K1B2 w - - 0 1");
    // b.show_board();
    cands0 = b.GetCandidates(S_RED);
    EXPECT_EQ(cands0.size(), 35);

    cands = b.GetCandidatesByPlayer(S_RED);
    // fmt::print("{} {}\n", cands, cands.size());
    EXPECT_EQ(cands.size(), 34);

    // 默认排除导致自杀的移动【将帅不可照脸】
    Coord from{4, 0};
    moveVec_t expected = {make_move("4030"), make_move("4041")};
    moveVec_t actual;
    std::for_each(cands.begin(), cands.end(), [from, &actual](const Move &m)
                  {if(m.from==from){actual.push_back(m);} });
    EXPECT_EQ(actual, expected);
}

// 士
TEST(BoardBasicTest, Runx09x2)
{
    moveVec_t cands0, cands;
    Board b;
    b.set_pieces("r4kb2/9/2n6/p3p3p/2p1P2N1/4C4/P1P2c2P/2cA3N1/4A4/2B2KB2 w - - 0 1");
    // b.show_board();
    cands0 = b.GetCandidates(S_RED);
    // fmt::print("{} {}\n", cands0, cands0.size());
    EXPECT_EQ(cands0.size(), 35);

    cands = b.GetCandidatesByPlayer(S_RED);
    // fmt::print("{} {}\n", cands, cands.size());
    EXPECT_EQ(cands.size(), 33);

    // 默认排除导致自杀的移动【士不可送将】
    Coord from{4, 1};
    moveVec_t expected = {make_move("4130")};
    moveVec_t actual;
    std::for_each(cands.begin(), cands.end(), [from, &actual](const Move &m)
                  {if(m.from==from){actual.push_back(m);} });
    EXPECT_EQ(actual, expected);
}

// 象
TEST(BoardBasicTest, Runx09x3)
{
    moveVec_t cands0, cands;
    Board b;
    b.set_pieces("r4kb2/9/2n6/p3p3p/2p1P4/4C4/P1Pc3NP/2cAB2NB/4A4/4K4 w - - 0 1");
    // b.show_board();
    cands0 = b.GetCandidates(S_RED);
    // fmt::print("{} {}\n", cands0, cands0.size());
    EXPECT_EQ(cands0.size(), 33);

    cands = b.GetCandidatesByPlayer(S_RED);
    // fmt::print("{} {}\n", cands, cands.size());
    EXPECT_EQ(cands.size(), 31);

    // 默认排除导致自杀的移动
    Coord from{4, 2};
    moveVec_t expected = {make_move("4220"), make_move("4260"), make_move("4264")};
    moveVec_t actual;
    std::for_each(cands.begin(), cands.end(), [from, &actual](const Move &m)
                  {if(m.from==from){actual.push_back(m);} });
    EXPECT_EQ(actual, expected);
}

// 马
TEST(BoardBasicTest, Runx09x4)
{
    moveVec_t cands0, cands;
    Board b;
    b.set_pieces("r4kb2/9/2n6/p3p3p/2p1P4/4C4/P1Pc3NP/2cAB2NB/4A4/4K4 w - - 0 1");
    // b.show_board();
    cands0 = b.GetCandidates(S_RED);
    // fmt::print("{} {}\n", cands0, cands0.size());
    EXPECT_EQ(cands0.size(), 33);

    cands = b.GetCandidatesByPlayer(S_RED);
    // fmt::print("{} {}\n", cands, cands.size());
    EXPECT_EQ(cands.size(), 31);

    Coord from{7, 2};
    moveVec_t expected = {make_move("7260"), make_move("7280"), make_move("7251"), make_move("7253")};
    moveVec_t actual;
    std::for_each(cands.begin(), cands.end(), [from, &actual](const Move &m)
                  {if(m.from==from){actual.push_back(m);} });
    // fmt::print("{} {}\n", actual, actual.size());
    EXPECT_EQ(actual, expected);
}

// 炮
TEST(BoardBasicTest, Runx09x5)
{
    moveVec_t cands0, cands;
    Board b;
    b.set_pieces("r4kb2/9/2n6/p3p3p/2p1P4/1nP1CcN2/P7P/2cAB2NB/4A4/4K4 w - - 0 1");
    // b.show_board();
    cands0 = b.GetCandidates(S_RED);
    // fmt::print("{} {}\n", cands0, cands0.size());
    EXPECT_EQ(cands0.size(), 27);

    cands = b.GetCandidatesByPlayer(S_RED);
    // fmt::print("{} {}\n", cands, cands.size());
    EXPECT_EQ(cands.size(), 27);

    Coord from{4, 4};
    moveVec_t expected = {make_move("4443"), make_move("4414"), make_move("4434"), make_move("4446")};
    moveVec_t actual;
    std::for_each(cands.begin(), cands.end(), [from, &actual](const Move &m)
                  {if(m.from==from){actual.push_back(m);} });
    // fmt::print("{} {}\n", actual, actual.size());
    EXPECT_EQ(actual, expected);
}

// 车
TEST(BoardBasicTest, Runx09x6)
{
    moveVec_t cands0, cands;
    Board b;
    b.set_pieces("r4kb2/9/2n6/p3p3p/4P4/1np1CcN2/P7P/3AB2NB/2R1A4/1c2K4 w - - 0 1");
    // b.show_board();
    cands0 = b.GetCandidates(S_RED);
    // fmt::print("{} {}\n", cands0, cands0.size());
    EXPECT_EQ(cands0.size(), 34);

    cands = b.GetCandidatesByPlayer(S_RED);
    // fmt::print("{} {}\n", cands, cands.size());
    EXPECT_EQ(cands.size(), 31);

    Coord from{2, 1};
    moveVec_t expected = {make_move("2101"), make_move("2111"), make_move("2131"), make_move("2122"), make_move("2123"), make_move("2124")};
    moveVec_t actual;
    std::for_each(cands.begin(), cands.end(), [from, &actual](const Move &m)
                  {if(m.from==from){actual.push_back(m);} });
    // fmt::print("{} {}\n", actual, actual.size());
    EXPECT_EQ(actual, expected);
}

// 兵
TEST(BoardBasicTest, Runx09x7)
{
    moveVec_t cands0, cands;
    Board b;
    b.set_pieces("r4kb2/9/2n6/p3p3p/4P4/1np1CcN2/P7P/3AB2NB/2R1A4/1c2K4 w - - 0 1");
    // b.show_board();
    cands0 = b.GetCandidates(S_RED);
    // fmt::print("{} {}\n", cands0, cands0.size());
    EXPECT_EQ(cands0.size(), 34);

    cands = b.GetCandidatesByPlayer(S_RED);
    // fmt::print("{} {}\n", cands, cands.size());
    EXPECT_EQ(cands.size(), 31);

    Coord from{4, 5};
    moveVec_t expected = {make_move("4535"), make_move("4555"), make_move("4546")};
    moveVec_t actual;
    std::for_each(cands.begin(), cands.end(), [from, &actual](const Move &m)
                  {if(m.from==from){actual.push_back(m);} });
    // fmt::print("{} {}\n", actual, actual.size());
    EXPECT_EQ(actual, expected);

    Coord from2{0, 3};
    moveVec_t expected2 = {make_move("0304")};
    moveVec_t actual2;
    std::for_each(cands.begin(), cands.end(), [from2, &actual2](const Move &m)
                  {if(m.from==from2){actual2.push_back(m);} });
    // fmt::print("{} {}\n", actual2, actual2.size());
    EXPECT_EQ(actual2, expected2);
}

// 移动候选
TEST(BoardBasicTest, Runx10x1)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces("r1b1kab2/4a4/2n6/p3p2Rp/2p1P4/9/P1P5P/2N1C2N1/3RA4/1cBAK1cr1 b - - 0 1");
    // b.show_board();
    // 实际应为内部函数，便于测试
    auto cands0 = b.GetCandidates(player);
    // 默认排除自杀
    auto cands1 = b.GetCandidatesByPlayer(player);
    // 没有导致自杀移动时，二者相等。因黑将不能送吃，二者相差一项
    EXPECT_EQ(cands0.size() - cands1.size(), 1);
    // fmt::print("cands0 {} {}\n", cands0, cands0.size());
    // fmt::print("cands1 {} {}\n", cands1, cands1.size());

    Coord jj_coord{7, 0};
    PieceType jj_piece = PieceType::ROOK;
    auto cands2 = b.GetCandidatesForCheck(player);
    // fmt::print("{} {}\n", cands2, cands2.size());
    // 测试实际将军坐标、棋子
    auto m1 = make_move("6030");
    for (auto m : cands2)
    {
        EXPECT_TRUE(m.is_check());
        EXPECT_EQ(m.info.jj_after_moved.size(), 1);
        EXPECT_EQ(m.info.jj_after_moved[0].coord, jj_coord);
        EXPECT_EQ(m.info.jj_after_moved[0].piece, jj_piece);
        if (m == m1)
        {
            EXPECT_TRUE(m.is_eat());
        }
    }

    // 所有候选都已经检查过走后是否将军、将军属性
    auto cands3 = b.GetCandidatesForEat(player);
    EXPECT_EQ(cands3.size(), 4);
    // fmt::print("{} {}\n", cands3, cands3.size());
    for (auto m : cands3)
    {
        EXPECT_TRUE(m.is_eat());
        // 吃同时将军
        if (m == m1)
        {
            EXPECT_TRUE(m.is_check());
        }
        else
        {
            EXPECT_FALSE(m.is_check());
        }
    }
}

TEST(BoardBasicTest, Runx10x2)
{
    Board b;
    Color player = S_RED;
    b.set_pieces("1r2kabr1/2c1a4/n1c1b1n2/4p2N1/p1p6/1C4P2/P1P1P4/2N1B3C/4A4/1RBAK2R1 w - - 0 1");
    // b.show_board();
    auto cands0 = b.GetCandidates(player);
    // 默认排除自杀
    auto cands1 = b.GetCandidatesByPlayer(player);
    // 没有导致自杀移动时，二者相等
    EXPECT_EQ(cands0, cands1);
    // fmt::print("cands0 {} {}\n", cands0, cands0.size());
    // fmt::print("cands1 {} {}\n", cands1, cands1.size());

    PieceType jj_piece = PieceType::HORSE;
    auto cands2 = b.GetCandidatesForCheck(player);
    // fmt::print("{} {}\n", cands2, cands2.size());
    // 测试实际将军坐标、棋子
    for (auto m : cands2)
    {
        EXPECT_TRUE(m.is_check());
        EXPECT_EQ(m.info.jj_after_moved.size(), 1);
        // 提子将军
        EXPECT_EQ(m.info.jj_after_moved[0].coord, m.to);
        EXPECT_EQ(m.info.jj_after_moved[0].piece, jj_piece);
    }

    // 所有候选都已经检查过走后是否将军、将军属性
    auto cands3 = b.GetCandidatesForEat(player);
    // fmt::print("{} {}\n", cands3, cands3.size());
    EXPECT_EQ(cands3.size(), 0);
}

TEST(BoardBasicTest, Runx10x3)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces("4kabr1/4a4/n3b1n2/7N1/p1p6/1C2c1P2/P3r4/2N1B3C/9/1RBAKA1R1 w - - 0 1");
    // b.show_board();
    // 实际应为内部函数，便于测试
    auto cands0 = b.GetCandidates(player);
    // 默认排除自杀
    auto cands1 = b.GetCandidatesByPlayer(player);
    EXPECT_EQ(cands0.size(), 37);
    EXPECT_EQ(cands0, cands1);
    // fmt::print("cands0 {} {}\n", cands0, cands0.size());
    // fmt::print("cands1 {} {}\n", cands1, cands1.size());

    Coord jj_coord{4, 4};
    PieceType jj_piece = PieceType::CANNON;
    auto cands2 = b.GetCandidatesForCheck(player);
    // fmt::print("{} {}\n", cands2, cands2.size());
    // // 测试实际将军坐标、棋子
    auto m1 = make_move("4342");
    for (auto m : cands2)
    {
        EXPECT_TRUE(m.is_check());
        if (m == m1)
        {
            // 车、炮同时将军
            EXPECT_EQ(m.info.jj_after_moved.size(), 2);
            // 吃象将
            EXPECT_TRUE(m.is_eat());
        }
        // 其他着法都是炮将军
        else
        {
            EXPECT_EQ(m.info.jj_after_moved[0].coord, jj_coord);
            EXPECT_EQ(m.info.jj_after_moved[0].piece, jj_piece);
        }
    }

    // 所有候选都已经检查过走后是否将军、将军属性
    auto m2 = make_move("4303");
    auto cands3 = b.GetCandidatesForEat(player);
    // fmt::print("{} {}\n", cands3, cands3.size());
    EXPECT_EQ(cands3.size(), 4);
    for (auto m : cands3)
    {
        EXPECT_TRUE(m.is_eat());
        // 吃同时将军
        if (m == m1 || m == m2)
        {
            EXPECT_TRUE(m.is_check());
        }
        else
        {
            EXPECT_FALSE(m.is_check());
        }
    }
}

TEST(BoardBasicTest, Runx10x4)
{
    Board b;
    b.set_pieces("1Cbak4/1r2a4/4b4/p8/4R3P/9/P8/4B1p2/4A4/2BAK4 r - - 0 1");
    auto m = make_move("4547");
    b.DoMove(m);
    Coord c{2, 9};
    // 测试是否生成会导致立即输棋的移动
    // 2947 无法飞象
    auto cands = b.GetCandidatesFrom(c);
    EXPECT_TRUE(cands.empty());
}

// 照将
TEST(BoardBasicTest, Runx11x1)
{
    Board b;
    b.clear();
    b.set_pieces({4, 0}, S_RED, PieceType::KING);
    b.set_pieces({4, 9}, S_BLACK, PieceType::KING);
    // b.show_board();
    EXPECT_TRUE(b.IsFace2Face());
}

// 将军状态
TEST(BoardBasicTest, Runx11x2)
{
    Board b;
    b.set_pieces("3a1k3/3N5/4ba3/9/2b6/9/9/9/1r2p4/3K5 r - - 0 1");
    // b.show_board();
    EXPECT_TRUE(b.IsCheck(S_RED));

    b.set_pieces("3a1k3/3N5/4ba3/9/2b6/9/9/9/1r2p4/3K5 b - - 0 1");
    // b.show_board();
    EXPECT_FALSE(b.IsCheck(S_BLACK));

    b.set_pieces("3a1k3/3Na4/4b4/9/2b6/9/9/9/4p4/1r1K5 b - - 0 1");
    // b.show_board();
    EXPECT_TRUE(b.IsCheck(S_BLACK));
}

// 局面重复
TEST(BoardBasicTest, Runx11x3)
{
    size_t t = 0;
    Board b;
    b.set_pieces("2b6/4k4/9/9/9/9/9/9/2p6/3K1RBc1 r - - 0 1");
    // b.show_board();
    auto move_1 = make_move("5040");
    auto move_2 = make_move("4858");
    auto move_3 = make_move("4050");
    auto move_4 = make_move("5848");
    b.DoMove(move_1);
    b.DoMove(move_2);
    b.DoMove(move_3);
    b.DoMove(move_4);
    EXPECT_EQ(b.repetition_size(), 0);
    b.DoMove(move_1);
    t = b.repetition_size();
    EXPECT_EQ(t, 4);
    EXPECT_TRUE(b.is_multi_repetitive(t, 1));
}

TEST(BoardBasicTest, Runx11x4)
{
    Board b;
    Move move;
    b.set_pieces(rule_china_02);

    move = make_move("7684");
    b.SimulateMove(move);

    // b.show_board(true, fmt::format("hash = {}", b.hash()));

    move = make_move("8979");
    b.SimulateMove(move);

    move = make_move("8476");
    b.SimulateMove(move);

    move = make_move("7989");
    b.SimulateMove(move);

    EXPECT_EQ(b.repetition_size(), 0);

    move = make_move("7684");
    b.SimulateMove(move);
    // b.show_board(true, fmt::format("hash = {}", b.hash()));

    auto t = b.repetition_size();
    EXPECT_EQ(t, 4);
    EXPECT_TRUE(b.is_multi_repetitive(t, 1));
    EXPECT_EQ(b.final_result(), DRAW);
}

// 模拟移动时，只要一次重复局面即判和
TEST(BoardBasicTest, Runx11x5)
{
    auto player = S_RED;
    Board b;
    Move move;
    b.set_pieces(rule_china_05);

    move = make_move("2924");
    b.DoMove(move);

    b.SetPlayer(player);

    move = make_move("2444");
    b.SimulateMove(move);
    // b.show_board(true, fmt::format("hash = {}", b.hash()));

    move = make_move("4858");
    b.SimulateMove(move);

    move = make_move("4454");
    b.SimulateMove(move);

    move = make_move("5848");
    b.SimulateMove(move);

    EXPECT_EQ(b.repetition_size(), 0);

    move = make_move("5444");
    b.SimulateMove(move);
    // b.show_board(true, fmt::format("hash = {}", b.hash()));

    EXPECT_EQ(b.repetition_size(), 4);
    EXPECT_EQ(b.final_result(), DRAW);
}

// 参考图42改编
// 移动不一定重复，局面重复
TEST(BoardBasicTest, Runx11x6)
{
    auto player = S_BLACK;
    Board b;
    Move move;
    b.set_pieces("9/5k3/2c6/p3R4/9/9/9/6n1B/5C3/r2AKA3 b - - 0 1");
    b.SetPlayer(player);

    move = make_move("2720");
    b.SimulateMove(move);

    move = make_move("3041");
    b.SimulateMove(move);
    // b.show_board(true, fmt::format("hash = {}", b.hash()));

    move = make_move("2021");
    b.SimulateMove(move);

    move = make_move("4130");
    b.SimulateMove(move);

    move = make_move("2120");
    b.SimulateMove(move);

    EXPECT_EQ(b.final_result(), DRAW);
}

// 被将死。走子方无子可走即被将死
TEST(BoardBasicTest, Runx11x8)
{
    std::string fen = "3a1k3/9/5P3/3R5/9/9/5r3/5C3/r2p5/4K4 w - - 0 1";
    Board b;
    b.set_pieces(fen);
    auto move = make_move("5758");
    b.SetPlayer(S_RED);
    b.DoMove(move);
    // b.show_board();
    EXPECT_TRUE(b.IsCheckmate(S_BLACK));

    b.undoMove();
    // 轮到黑方走子
    b.SetPlayer(S_BLACK);
    move = make_move("0100");
    b.DoMove(move);
    // b.show_board();
    EXPECT_TRUE(b.IsCheckmate(S_RED));
}

TEST(BoardBasicTest, Runx11x9)
{
    std::string fen = "3a1k3/3Na4/5P1R1/9/2b6/9/9/1r1p5/4An3/3K1A3 w - - 0 1";
    Board b;
    Move move = make_move("7779");
    b.set_pieces(fen);
    b.SetPlayer(S_RED);
    b.DoMove(move);
    // b.show_board();
    EXPECT_TRUE(b.IsCheckmate(S_BLACK));

    b.undoMove();
    // 轮到黑方走子
    b.SetPlayer(S_BLACK);
    move = make_move("1210");
    b.DoMove(move);
    // b.show_board();
    EXPECT_TRUE(b.IsCheckmate(S_RED));
}

// 测试执行移动
TEST(BoardBasicTest, Runx12x1)
{
    Board b;
    Move move;
    b.set_pieces(rule_china_02);

    b.SetResult(1);
    move = make_move("2324");

    // 游戏结束后，无法执行移动
    EXPECT_THROW(b.DoMove(move), std::out_of_range);
}

// 执行移动后修改移动**将军**属性
// 执行移动后修改移动**吃子**属性
TEST(BoardBasicTest, Runx12x2)
{
    Board b;
    Move move;
    // 图02改编
    b.set_pieces("1r2kabr1/2c1a4/n1c1b1n2/4p2N1/p1p6/1C4P2/P1P1P4/2N1B3C/4A4/1RBAK2R1 w - - 0 1");

    move = make_move("7668");
    EXPECT_FALSE(move.is_check());

    b.DoMove(move);
    EXPECT_TRUE(move.is_check());
    EXPECT_EQ(move.info.jj_after_moved[0].coord, move.to);

    move = make_move("2868");
    EXPECT_FALSE(move.is_eat());

    b.DoMove(move);
    EXPECT_TRUE(move.is_eat());
    EXPECT_EQ(move.info.tgt.coord, move.to);

    move = make_move("7079");
    EXPECT_FALSE(move.is_eat());

    b.DoMove(move);
    EXPECT_TRUE(move.is_eat());
    EXPECT_FALSE(move.is_check());
    EXPECT_EQ(move.info.tgt.coord, move.to);
}

// 被吃掉将、帅
TEST(BoardBasicTest, Runx12x3)
{
    Board b;
    Move move;
    // 图02改编
    b.set_pieces("1r2kabr1/2c1a4/n1c1b1n2/4p2N1/p1p6/1C4P2/P1P1P4/2N1B3C/4A4/1RBAK2R1 w - - 0 1");

    move = make_move("7668");
    b.DoMove(move);
    // 黑方本应应将
    move = make_move("1914");
    b.DoMove(move);

    move = make_move("6849");
    b.DoMove(move);

    EXPECT_TRUE(b.is_game_ended());
    EXPECT_EQ(b.final_result(), RED_WIN);

    move = make_move("2868");
    EXPECT_THROW(b.DoMove(move), std::out_of_range);
}

// 模拟运行
// 为防止模拟过程中的多次无效重复，重复一次即判和
TEST(BoardBasicTest, Runx13x1)
{
    size_t t = 0;
    Board b;
    b.set_pieces("2b6/4k4/9/9/9/9/9/9/2p6/3K1RBc1 r - - 0 1");
    // b.show_board();
    auto move_1 = make_move("5040");
    auto move_2 = make_move("4858");
    auto move_3 = make_move("4050");
    auto move_4 = make_move("5848");
    b.SimulateMove(move_1);
    b.SimulateMove(move_2);
    b.SimulateMove(move_3);
    b.SimulateMove(move_4);
    EXPECT_EQ(b.repetition_size(), 0);
    b.SimulateMove(move_1);
    t = b.repetition_size();
    EXPECT_EQ(t, 4);
    EXPECT_TRUE(b.is_multi_repetitive(t, 1));

    EXPECT_TRUE(b.is_game_ended());
    EXPECT_EQ(b.final_result(), DRAW);
}

TEST(BoardBasicTest, Runx13x2)
{
    Board b;
    Move move;
    b.set_pieces(rule_china_02);

    move = make_move("7684");
    b.SimulateMove(move);

    move = make_move("8979");
    b.SimulateMove(move);

    move = make_move("8476");
    b.SimulateMove(move);

    move = make_move("7989");
    b.SimulateMove(move);

    EXPECT_EQ(b.repetition_size(), 0);

    move = make_move("7684");
    b.SimulateMove(move);

    auto t = b.repetition_size();
    EXPECT_EQ(t, 4);
    EXPECT_TRUE(b.is_multi_repetitive(t, 1));

    EXPECT_TRUE(b.is_game_ended());
    EXPECT_EQ(b.final_result(), DRAW);
}

// 游戏结果
TEST(BoardBasicTest, Runx14x1)
{
    Board b;
    Move move;
    b.set_pieces("3k1a3/4a4/b3b4/9/9/4R4/4n4/3Ar4/3KA4/9 b - - 0 1");

    // fmt::print("{}\n", b.flipup().get_fen_string());

    move = make_move("4232");
    b.SimulateMove(move);

    // 红方被将死
    EXPECT_TRUE(b.is_game_ended());
    EXPECT_EQ(b.final_result(), RED_LOSE);
}

TEST(BoardBasicTest, Runx14x2)
{
    Board b;
    Move move;
    b.set_pieces("9/4ak3/4Ra3/4N4/4r4/9/9/4B3B/4A4/3A1K3 w - - 0 1");

    move = make_move("4757");
    b.SimulateMove(move);

    // 黑方被将死
    EXPECT_TRUE(b.is_game_ended());
    EXPECT_EQ(b.final_result(), RED_WIN);
}

TEST(BoardBasicTest, Runx14x3)
{
    Board b;
    Move move;
    b.set_pieces("rnbRkabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBK1ABN1 b - - 0 1");

    move = make_move("4939");
    b.SimulateMove(move);

    // 黑方走子后形成将帅照面
    EXPECT_TRUE(b.is_game_ended());
    EXPECT_EQ(b.final_result(), RED_WIN);
}

TEST(BoardBasicTest, Runx14x4)
{
    Board b;
    Move move;
    b.set_pieces("1nbk1abnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBrKABN1 w - - 0 1");

    move = make_move("4030");
    b.SimulateMove(move);

    // 红方走子后形成将帅照面
    EXPECT_TRUE(b.is_game_ended());
    EXPECT_EQ(b.final_result(), RED_LOSE);
}

// 联合将军
TEST(BoardBasicTest, Runx15x1)
{
    Board b;
    b.set_pieces("rnbakabnr/9/1c5c1/p1p3p1p/9/2C6/P1P3P1P/4C1N2/9/RNBAKAB1R w - - 0 1");

    auto jjs = b.GetCandidatesForCheck(S_RED);
    // 联合将军
    auto move1 = make_move("6243");
    auto found1 = *std::find(jjs.begin(), jjs.end(), move1);
    EXPECT_TRUE(found1.is_check());
    EXPECT_TRUE(found1.is_jointed_check());

    auto move2 = make_move("2429");
    auto found2 = *std::find(jjs.begin(), jjs.end(), move2);
    EXPECT_TRUE(found2.is_check());
    EXPECT_FALSE(found2.is_jointed_check());
}

TEST(BoardBasicTest, Runx16x1)
{
    Board b1;
    b1.clear();
    b1.set_pieces('R', {3, 9});
    b1.set_pieces('k', {3, 7});
    b1.set_pieces('R', {5, 8});

    b1.set_pieces('B', {2, 4});
    b1.set_pieces('B', {4, 2});
    b1.set_pieces('n', {0, 3});
    b1.set_pieces('p', {3, 2});
    b1.set_pieces('p', {4, 1});
    b1.set_pieces('K', {3, 0});
    // b1.show_board();
    auto h1 = b1.hash();

    Board b2;
    b2.clear();
    b2.set_pieces('R', {3, 9});
    b2.set_pieces('k', {3, 7});
    b2.set_pieces('R', {5, 8});

    b2.set_pieces('B', {2, 4});
    b2.set_pieces('B', {4, 2});
    b2.set_pieces('n', {0, 3});
    b2.set_pieces('p', {3, 2});
    b2.set_pieces('p', {4, 1});
    b2.set_pieces('K', {3, 0});
    // b2.show_board();
    auto h2 = b2.hash();

    EXPECT_EQ(h1, h2);

    Board b3 = b1.clone();
    EXPECT_EQ(h1, b3.hash());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}