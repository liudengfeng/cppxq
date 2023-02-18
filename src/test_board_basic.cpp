#include <gtest/gtest.h>

#include "common.hpp"
#include "board.hpp"
#include "test_cases.hpp"

// [==========] Running 15 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 15 tests from BoardBasicTest
// [ RUN      ] BoardBasicTest.testShowBoard
// [       OK ] BoardBasicTest.testShowBoard (0 ms)
// [ RUN      ] BoardBasicTest.testGetLastMove
// [       OK ] BoardBasicTest.testGetLastMove (0 ms)
// [ RUN      ] BoardBasicTest.testHasRootx1
// [       OK ] BoardBasicTest.testHasRootx1 (0 ms)
// [ RUN      ] BoardBasicTest.testHasRootx2x1
// [       OK ] BoardBasicTest.testHasRootx2x1 (0 ms)
// [ RUN      ] BoardBasicTest.testHasRootx2x2
// [       OK ] BoardBasicTest.testHasRootx2x2 (0 ms)
// [ RUN      ] BoardBasicTest.testHasRootx3
// [       OK ] BoardBasicTest.testHasRootx3 (0 ms)
// [ RUN      ] BoardBasicTest.testHasRootx4x1
// [       OK ] BoardBasicTest.testHasRootx4x1 (1 ms)
// [ RUN      ] BoardBasicTest.testHasRootx4x2
// [       OK ] BoardBasicTest.testHasRootx4x2 (1 ms)
// [ RUN      ] BoardBasicTest.testAttacked
// [       OK ] BoardBasicTest.testAttacked (0 ms)
// [ RUN      ] BoardBasicTest.testUndoMove
// [       OK ] BoardBasicTest.testUndoMove (0 ms)
// [ RUN      ] BoardBasicTest.testUndoNSteps
// [       OK ] BoardBasicTest.testUndoNSteps (0 ms)
// [ RUN      ] BoardBasicTest.testGetLastMoves
// [       OK ] BoardBasicTest.testGetLastMoves (0 ms)
// [ RUN      ] BoardBasicTest.testConvert
// [       OK ] BoardBasicTest.testConvert (0 ms)
// [ RUN      ] BoardBasicTest.testRunx01
// [       OK ] BoardBasicTest.testRunx01 (0 ms)
// [ RUN      ] BoardBasicTest.testRootx01
// [       OK ] BoardBasicTest.testRootx01 (0 ms)
// [----------] 15 tests from BoardBasicTest (7 ms total)

// [----------] Global test environment tear-down
// [==========] 15 tests from 1 test suite ran. (7 ms total)
// [  PASSED  ] 15 tests.

TEST(BoardBasicTest, testShowBoard)
{
    Board b;
    b.set_pieces("3ak4/4a1P2/9/9/9/9/9/9/9/4K4 r - - 0 1");
    // b.show_board();
    auto m = make_move("6858");
    b.DoMove(m);
    EXPECT_EQ(b.final_result(), 1);
    // b.show_board();

    b.undoMove();
    auto m2 = make_move("6869");
    b.DoMove(m2);
    EXPECT_EQ(b.final_result(), 1);
    // b.show_board(true);
}

TEST(BoardBasicTest, testGetLastMove)
{
    Board b;

    // Move dumpy = make_move("0002");
    // b.DoMove(dumpy);
    // EXPECT_EQ(b.get_last_move(), dumpy);

    auto move = make_move("0001");
    b.DoMove(move);
    auto actual = b.get_last_move();
    EXPECT_EQ(actual, move);

    auto move2 = make_move("8987");
    b.DoMove(move2);
    EXPECT_EQ(b.get_last_move(), move2);
}

// 棋子是否有根保护
TEST(BoardBasicTest, testHasRootx1)
{
    Board b;
    // b.show_board();
    auto h = b.hash();
    Coord c{1, 9};
    EXPECT_TRUE(b.HasRootProtected(c));
    // b.show_board();
    // 确认没有更改hash
    EXPECT_EQ(b.hash(), h);
}

// 如上，(2,9) 位置的象无法对(4,7)的象提供保护，为假根
// 假根不列入根保护范围
TEST(BoardBasicTest, testHasRootx2x1)
{
    Board b;
    b.set_pieces(rule_china_11);
    // b.show_board();
    Coord c{4, 7};
    EXPECT_FALSE(b.HasRootProtected(c));
}

TEST(BoardBasicTest, testHasRootx2x2)
{
    Board b;
    b.set_pieces(rule_china_11);
    // b.show_board();
    Coord c{4, 7};
    // 假根保护
    EXPECT_TRUE(b.IsFakeRootProtected(c));
}

TEST(BoardBasicTest, testHasRootx3)
{
    Board b;
    b.set_pieces("3k2P2/P3a4/2c1b1rc1/7R1/6b2/9/9/B3B4/4A4/4KA3 b - - 0 1");
    // b.show_board();
    EXPECT_TRUE(b.HasRootProtected({6, 7}, {7, 7}));
    EXPECT_TRUE(b.HasRootProtected({6, 7}, {6, 5}));
    EXPECT_FALSE(b.HasRootProtected({6, 7}, {2, 7}));
    EXPECT_FALSE(b.HasRootProtected({7, 8}, {7, 7}));
}

TEST(BoardBasicTest, testHasRootx4x1)
{
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256"), make_move("1216"), make_move("5652")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_FALSE(b.HasRootProtected(Coord{6, 2}));
}

TEST(BoardBasicTest, testHasRootx4x2)
{
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256"), make_move("1216"), make_move("5652")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(b.HasRootProtected(Coord{4, 6}));
    EXPECT_EQ(b.NumberOfProtected(Coord{4, 6}), 2);
}

TEST(BoardBasicTest, testNoEatx01)
{
    Board b;
    b.set_pieces("9/5k3/6P2/9/9/9/9/9/9/4K4 r");
    EXPECT_EQ(b.no_eat(), 0);
    /// 默认不包含，但规范fen还是设置no eat
    b.set_pieces("9/5k3/6P2/9/9/9/9/9/9/4K4 r - 116 0 1");
    EXPECT_EQ(b.no_eat(), 116);
}

TEST(BoardBasicTest, testNoEatx02)
{
    Board b;
    /// 默认不包含，但规范fen还是设置no eat
    b.set_pieces("3ak1NrC/4a4/4b4/9/9/9/9/9/2p1r4/3K5 r - 110 0 1");
    EXPECT_EQ(b.no_eat(), 110);
    auto move1 = make_move("6948");
    b.DoMove(move1);
    EXPECT_EQ(b.no_eat(), 0);
    auto move2 = make_move("4948");
    b.DoMove(move2);
    EXPECT_EQ(b.no_eat(), 0);
    auto move3 = make_move("8988");
    b.DoMove(move3);
    EXPECT_EQ(b.no_eat(), 1);
}

// 棋子是否受到攻击威胁
TEST(BoardBasicTest, testAttacked)
{
    Board b;
    Coord c1{1, 9};
    EXPECT_TRUE(b.BeingAttacked(c1));

    Coord c2{1, 0};
    EXPECT_TRUE(b.BeingAttacked(c2));
}

TEST(BoardBasicTest, testUndoMove)
{
    Board b;
    auto move_1 = make_move("1242");
    auto move_2 = make_move("7967");
    auto move_3 = make_move("4246");
    b.DoMove(move_1);
    b.DoMove(move_2);
    b.DoMove(move_3);
    EXPECT_EQ(b.get_last_move(), move_3);
    EXPECT_EQ(b.steps(), 4);

    auto h0 = b.hash();
    // b.show_board(true);
    b.undoMove();
    auto h1 = b.hash();
    EXPECT_FALSE(h0 == h1);
    EXPECT_EQ(b.keys().back(), h1);
    // b.show_board(true);
    EXPECT_EQ(b.get_last_move(), move_2);
    EXPECT_EQ(b.steps(), 3);
}

TEST(BoardBasicTest, testUndoNSteps)
{
    Board b;
    b.set_pieces("2bak1c2/4aRN1r/4b4/9/9/9/3pp4/2n1B4/9/2B1K3C r - - 0 1");
    // b.show_board();

    auto move_1 = make_move("8070");
    auto move_2 = make_move("8878");
    auto move_3 = make_move("4260");
    auto move_4 = make_move("7870");

    b.DoMove(move_1);
    b.DoMove(move_2);
    b.DoMove(move_3);
    // 连续三步未吃子 第二回合 累计步数3步【从1开始】
    EXPECT_EQ("2bak1c2/4aRNr1/4b4/9/9/9/3pp4/2n6/9/2B1K1BC1 b - 3 2 4", b.get_fen_string(false, false, true));
    // std::cout << b.get_fen_string(false, false, true) << std::endl;
    b.DoMove(move_4);
    // std::cout << b.get_fen_string(false, false, true) << std::endl;
    EXPECT_EQ("2bak1c2/4aRN2/4b4/9/9/9/3pp4/2n6/9/2B1K1Br1 r - 0 2 5", b.get_fen_string(false, false, true));
    // b.show_board();

    int n = 4;
    b.undoNSteps(n);

    // b.show_board();
    // std::cout << b.get_fen_string() << std::endl;
    EXPECT_EQ("2bak1c2/4aRN1r/4b4/9/9/9/3pp4/2n1B4/9/2B1K3C r - - 0 1", b.get_fen_string(false, false, false));
    EXPECT_EQ(1, b.steps());
}

TEST(BoardBasicTest, testGetLastMoves)
{
    Board b;
    b.set_pieces("2bak1c2/4aRN1r/4b4/9/9/9/3pp4/2n1B4/9/2B1K3C r - - 0 1");
    // b.show_board();

    auto move_1 = make_move("8070");
    auto move_2 = make_move("8878");
    auto move_3 = make_move("4262");
    auto move_4 = make_move("7870");

    b.DoMove(move_1);
    b.DoMove(move_2);
    b.DoMove(move_3);
    b.DoMove(move_4);

    auto moves1 = b.get_last_moves(5);
    EXPECT_TRUE(moves1.empty());

    auto moves2 = b.get_last_moves(4);
    EXPECT_EQ(moves2.size(), 4);
    EXPECT_EQ(moves2[0], move_1);
    EXPECT_EQ(moves2[3], move_4);

    auto moves3 = b.get_last_moves(3);
    EXPECT_EQ(moves3.size(), 3);
    EXPECT_EQ(moves3[0], move_2);
    EXPECT_EQ(moves3[2], move_4);
}

// 转换
TEST(BoardBasicTest, testConvert)
{
    Board b1, b2;
    b1.set_pieces("2b6/4k4/9/9/9/9/9/9/2p6/3K1RBc1 r - - 0 1");
    EXPECT_EQ(b1.next_player(), S_RED);
    // b1.show_board();
    b2 = b1.flipup();
    // b2.show_board();
    // fmt::print(b2.get_fen_string());
    EXPECT_EQ(b2.get_fen_string(), "1Cbr1k3/6P2/9/9/9/9/9/9/4K4/6B2 b - 0 0 1");
    EXPECT_EQ(b2.flipup().get_fen_string(), "2b6/4k4/9/9/9/9/9/9/2p6/3K1RBc1 r - 0 0 1");
}

TEST(BoardBasicTest, testRunx01)
{
    Board b;
    Move move;
    b.set_pieces("2b1ka3/4a4/n1c1b1n2/p3p3p/6p2/2rN1N1R1/P3P3P/4B2C1/4A4/2BAK4 w - - 0 1");

    // 红方不能吃车，否则黑方一步杀
    move = make_move("4224");
    // b.show_board();
    // fmt::print(b2.get_fen_string());
    EXPECT_TRUE(b.immediately_loss_once_moved(move));
}

TEST(BoardBasicTest, testRootx01)
{
    Board b;
    Move move;
    b.set_pieces(rule_china_12);
    // b.show_board();
    auto ps = b.RootProtectedCoords(Coord(7, 7));
    EXPECT_EQ(ps.size(), 1);
    EXPECT_EQ(ps[0], Coord(6, 7));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}