#include <gtest/gtest.h>

#include "test_cases.hpp"
#include "rule2022.hpp"

#include "test_helper.hpp"

using namespace rule2022;

// [==========] Running 21 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 21 tests from ShaSimulate
// [ RUN      ] ShaSimulate.Candsx01
// [       OK ] ShaSimulate.Candsx01 (0 ms)
// [ RUN      ] ShaSimulate.Candsx02x1
// [       OK ] ShaSimulate.Candsx02x1 (2 ms)
// [ RUN      ] ShaSimulate.Candsx02x2
// [       OK ] ShaSimulate.Candsx02x2 (2 ms)
// [ RUN      ] ShaSimulate.Candsx02x3
// [       OK ] ShaSimulate.Candsx02x3 (0 ms)
// [ RUN      ] ShaSimulate.Candsx02x4
// [       OK ] ShaSimulate.Candsx02x4 (6 ms)
// [ RUN      ] ShaSimulate.Candsx03x1
// [       OK ] ShaSimulate.Candsx03x1 (0 ms)
// [ RUN      ] ShaSimulate.Runx01x1
// [       OK ] ShaSimulate.Runx01x1 (0 ms)
// [ RUN      ] ShaSimulate.Runx01x2
// [       OK ] ShaSimulate.Runx01x2 (1 ms)
// [ RUN      ] ShaSimulate.Runx02
// [       OK ] ShaSimulate.Runx02 (26 ms)
// [ RUN      ] ShaSimulate.Runx03
// [       OK ] ShaSimulate.Runx03 (3 ms)
// [ RUN      ] ShaSimulate.Runx04
// [       OK ] ShaSimulate.Runx04 (366 ms)
// [ RUN      ] ShaSimulate.Runx05x1
// [       OK ] ShaSimulate.Runx05x1 (519 ms)
// [ RUN      ] ShaSimulate.Runx06
// [       OK ] ShaSimulate.Runx06 (411 ms)
// [ RUN      ] ShaSimulate.Runx07
// [       OK ] ShaSimulate.Runx07 (7 ms)
// [ RUN      ] ShaSimulate.Runx08
// [       OK ] ShaSimulate.Runx08 (48 ms)
// [ RUN      ] ShaSimulate.Runx09
// [       OK ] ShaSimulate.Runx09 (0 ms)
// [ RUN      ] ShaSimulate.Runx10
// [       OK ] ShaSimulate.Runx10 (32 ms)
// [ RUN      ] ShaSimulate.Runx11
// [       OK ] ShaSimulate.Runx11 (0 ms)
// [ RUN      ] ShaSimulate.Runx12
// [       OK ] ShaSimulate.Runx12 (12 ms)
// [ RUN      ] ShaSimulate.Runx13
// [       OK ] ShaSimulate.Runx13 (112 ms)
// [ RUN      ] ShaSimulate.Runx14
// [       OK ] ShaSimulate.Runx14 (251 ms)
// [----------] 21 tests from ShaSimulate (1807 ms total)

// [----------] Global test environment tear-down
// [==========] 21 tests from 1 test suite ran. (1807 ms total)
// [  PASSED  ] 21 tests.

TEST(ShaSimulate, Candsx01)
{
    Board b;
    auto player = S_RED;
    b.set_pieces("2b1R4/9/3k5/2N6/9/9/9/2pA5/3KAp3/2r6 w - - 0 1");
    // b.show_board();

    ShaSimulator simulator(b, player);
    b.SetPlayer(player);

    auto node_ptr = simulator.root;
    // 根节点
    EXPECT_TRUE(node_ptr->is_root());

    // 返回一个可行的杀
    auto cands = simulator.get_cands(node_ptr, b);
    // fmt::print("{}\n", cands);
    EXPECT_EQ(cands.size(), 1);
    auto move = make_move("4939");
    EXPECT_TRUE(contains(cands, move));
}

TEST(ShaSimulate, Candsx02x1)
{
    Board b;
    auto player = S_RED;
    b.set_pieces("nPb2C3/5nP2/b3k4/1C7/2p1PRp2/4r4/P8/cp2B4/2p1p4/1c1KR2r1 w - - 0 1");
    b.ClearPiece(Coord(5, 9));
    // b.show_board();

    ShaSimulator simulator(b, player);
    b.SetPlayer(player);

    auto node_ptr = simulator.root;
    auto cands = simulator.get_cands(node_ptr, b);
    // fmt::print("{}\n", cands);
    EXPECT_EQ(cands.size(), 2);
    auto move = make_move("5557");
    EXPECT_TRUE(contains(cands, move));

    node_ptr->expand(cands);
    EXPECT_EQ(node_ptr->children.size(), 2);
    // 使用将军后对手可吃的移动
    node_ptr = node_ptr->children[1];
    // node_ptr->print(player);

    b.DoMove(move);
    cands = simulator.get_cands(node_ptr, b);
    // 测试是否将吃回优先
    // fmt::print("{}\n", cands);
    // 二种应将着法，吃优先
    EXPECT_EQ(cands.size(), 2);
    move = make_move("4757");
    EXPECT_EQ(cands[0], move);
}

TEST(ShaSimulate, Candsx02x2)
{
    Board b;
    b.set_pieces("nPb2C3/5nP2/b3k4/1C7/2p1PRp2/4r4/P8/cp2B4/2p1p4/1c1KR2r1 w - - 0 1");
    // b.show_board();

    auto player = S_RED;
    ShaSimulator simulator(b, player);
    b.SetPlayer(player);

    auto node_ptr = simulator.root;
    auto cands = simulator.get_cands(node_ptr, b);
    // fmt::print("{}\n", cands);
    EXPECT_EQ(cands.size(), 2);
    auto move = make_move("4546");
    EXPECT_TRUE(contains(cands, move));

    node_ptr->expand(cands);
    EXPECT_EQ(node_ptr->children.size(), 2);
    // 使用将军后对手可吃的移动
    node_ptr = node_ptr->children[0];
    // node_ptr->print(player);

    b.DoMove(move);

    cands = simulator.get_cands(node_ptr, b);
    // 测试是否将吃回优先
    // fmt::print("{}\n", cands);
    // 三种应将着法，吃优先
    EXPECT_EQ(cands.size(), 3);
    auto move1 = make_move("4446");
    EXPECT_EQ(cands[0], move1);

    auto move2 = make_move("5846");
    EXPECT_EQ(cands[1], move2);

    auto move3 = make_move("4748");
    EXPECT_EQ(cands[2], move3);
}

TEST(ShaSimulate, Candsx02x3)
{
    Board b;
    auto player = S_RED;
    b.set_pieces("nPb2C3/5nP2/b3k4/1C7/2p1PRp2/4r4/P8/cp2B4/2p1p4/1c1KR2r1 w - - 0 1");
    // b.show_board();

    ShaSimulator simulator(b, player);
    b.SetPlayer(player);

    auto node_ptr = simulator.root;
    // auto cands = simulator.get_cands(node_ptr, b);

    auto cands = b.GetCandidatesForCheck(player);
    // fmt::print("{}\n", cands);
    EXPECT_EQ(cands.size(), 2);
    auto move = make_move("4546");
    EXPECT_TRUE(contains(cands, move));
}

// 参考图 25 改编
TEST(ShaSimulate, Candsx02x4)
{
    Board b;
    auto player = S_RED;
    b.set_pieces("2bak1b2/4a2r1/4c1n2/p7p/2p2rpc1/4R4/P1PR2P1P/2N1C1N2/4A4/2BK1AB2 w - - 0 1");
    // b.show_board();

    ShaSimulator simulator(b, player);
    b.SetPlayer(player);

    auto node_ptr = simulator.root;
    auto board = simulator.init_board;

    // 1. 将军
    auto cands0 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands0);
    EXPECT_EQ(cands0.size(), 2);

    node_ptr->expand(cands0);
    node_ptr = node_ptr->children[1];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 3339");

    board.SimulateMove(node_ptr->history.back());

    // 2. 应将
    auto cands1 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands1);
    EXPECT_EQ(cands1.size(), 1);
    // 应将时吃优先
    EXPECT_EQ(cands1[0], make_move("4839"));

    node_ptr->expand(cands1);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 3339 -> 4839");

    board.SimulateMove(node_ptr->history.back());

    // 3. 将军
    auto cands2 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands2);
    EXPECT_EQ(cands2.size(), 9);

    node_ptr->expand(cands2);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 3339 -> 4839 -> 4404");

    board.SimulateMove(node_ptr->history.back());

    // 4. 应将
    auto cands3 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands3);
    EXPECT_EQ(cands3.size(), 12);
    EXPECT_EQ(cands3[0], make_move("4959"));
}

// 反杀
TEST(ShaSimulate, Candsx03x1)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_07);
    // b.show_board();

    ShaSimulator simulator(b, player);
    b.SetPlayer(player);

    auto node_ptr = simulator.root;
    auto cands = simulator.get_cands(node_ptr, b);
    // fmt::print("{}\n", cands);
    EXPECT_EQ(cands.size(), 1);
    auto move = make_move("8880");
    EXPECT_TRUE(contains(cands, move));

    node_ptr->expand(cands);
    node_ptr = node_ptr->children[0];

    b.DoMove(move);

    // 存在反杀
    cands = simulator.get_cands(node_ptr, b);
    EXPECT_EQ(cands.size(), 1);
    // fmt::print("{}\n", cands);
    auto sha = make_move("5850");
    EXPECT_TRUE(contains(cands, sha));
}

// ➡️ 一步杀
TEST(ShaSimulate, Runx01x1)
{
    Board b;
    Move move;
    auto player = S_BLACK;
    b.set_pieces(rule_china_18);

    move = make_move("4434");
    b.DoMove(move);

    move = make_move("3949");
    b.DoMove(move);

    move = make_move("3444");
    b.DoMove(move);

    move = make_move("4939");
    b.DoMove(move);
    // b.show_board();

    ShaSimulator simulator(b, player);
    simulator.run();

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 4232");

    EXPECT_TRUE(simulator.IsTrue());
    EXPECT_EQ(simulator.times(), 1);
}

// 反杀
TEST(ShaSimulate, Runx01x2)
{
    Board b;
    auto player = S_RED;
    b.set_pieces("2b1k4/2R1a1r2/4b2R1/p3C3P/4c4/9/9/1r1AB4/4A4/4K4 w - - 0 1");
    // b.show_board(true, "杀模拟");
    ShaSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 2829");
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(ShaSimulate, Runx02)
{
    Board b;
    Move move;
    b.set_pieces(rule_china_19);

    move = make_move("3646");
    b.DoMove(move);

    move = make_move("3717");
    b.DoMove(move);
    // b.show_board(true, "杀模拟");

    auto player = S_BLACK;
    ShaSimulator simulator(b, player);
    EXPECT_TRUE(simulator.IsTrue());

    auto n = simulator.ReasonablePath();
    // EXPECT_EQ(n->path(), "root -> 2320 -> 4220 -> 7152");
    EXPECT_EQ(n->path(), "root -> 2320 -> 4130 -> 2030 -> 4041 -> 3031 -> 4140 -> 7152");
    EXPECT_EQ(simulator.times(), 10);
}

TEST(ShaSimulate, Runx03)
{
    Board b;
    b.set_pieces("8R/3Nck3/9/5N2c/9/9/9/5p3/4p3r/5K3 w - - 0 1");
    // b.show_board(true, "杀模拟");

    auto player = S_RED;
    ShaSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 5637 -> 4847 -> 8988");
    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
}

// 2045 ms
// 3743 ms
TEST(ShaSimulate, Runx04)
{
    Board b;
    b.set_pieces(rule_china_07);

    auto move = make_move("8070");
    b.DoMove(move);
    // b.show_board(true, "杀模拟");

    auto player = S_RED;
    ShaSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 7079 -> 4859 -> 5859 -> 4948 -> 6856 -> 4838 -> 5939");
    EXPECT_EQ(simulator.times(), 113);
    EXPECT_TRUE(simulator.IsTrue());
}

// 6044 ms
TEST(ShaSimulate, Runx05x1)
{
    Board b;
    b.set_pieces("4nab2/4ac3/5k1n1/4P4/p5b2/1C7/3R3N1/1rR1p4/2r2p3/4K4 w - - 0 1");
    // b.show_board(true, "杀模拟");

    auto player = S_RED;
    // 耗时
    ShaSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();

    // EXPECT_EQ(n->path(), "root -> 3337 -> 6547 -> 4647");
    EXPECT_EQ(n->path(), "root -> 3337 -> 4837 -> 7365 -> 7765 -> 1417 -> 1217 -> 4647 -> 5747 -> 2242 -> 6544 -> 4244 -> 4757 -> 4447");
    EXPECT_EQ(simulator.times(), 134);
    EXPECT_TRUE(simulator.IsTrue());
}

// 52469 ms
// TEST(ShaSimulate, Runx05x2)
// {
//     Board b;
//     b.set_pieces("4nab2/4ac3/5k1n1/4P4/p5b2/1C7/3R3N1/1rR1p4/2r2p3/4K4 w - - 0 1");
//     // b.show_board(true, "杀模拟");

//     auto player = S_RED;
//     // 耗时
//     ShaSimulator simulator(b, player);
//     simulator.cut_passed = false;

//     auto n = simulator.ReasonablePath();

//     // EXPECT_EQ(n->path(), "root -> 3337 -> 6547 -> 4647");
//     EXPECT_EQ(n->path(), "root -> 3337 -> 4837 -> 7365 -> 7765 -> 1417 -> 1217 -> 4647 -> 5747 -> 2242 -> 6544 -> 4244 -> 4757 -> 4447");
//     EXPECT_EQ(simulator.times(), 1044);
//     EXPECT_TRUE(simulator.IsTrue());
// }

// ➡️ 用时 2932 ms
// ➡️ 用时 6085 ms
TEST(ShaSimulate, Runx06)
{
    Board b;
    Move move;
    auto player = S_BLACK;
    b.set_pieces(rule_china_17);

    // b.show_board(true, "杀模拟");

    ShaSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 2720 -> 4041 -> 7771 -> 4142 -> 7172 -> 4241 -> 2021 -> 4140 -> 7242 -> 4030 -> 2120 -> 3031 -> 4232 -> 3141 -> 2021 -> 4140 -> 3230");
    EXPECT_EQ(simulator.times(), 105);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(ShaSimulate, Runx07)
{
    Board b;
    Move move;
    auto player = S_RED;
    b.set_pieces(rule_china_20);

    move = make_move("1608");
    b.DoMove(move);

    // b.show_board();

    ShaSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 0829 -> 4839 -> 2937 -> 4948 -> 0608 -> 2628 -> 0828");
    EXPECT_EQ(simulator.times(), 3);
}

TEST(ShaSimulate, Runx08)
{
    Board b;
    Move move;
    auto player = S_BLACK;
    b.set_pieces(rule_china_29);

    move = make_move("8373");
    b.DoMove(move);

    move = make_move("7989");
    b.DoMove(move);

    // b.show_board(true, "杀模拟");

    ShaSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 8980 -> 4041 -> 0001 -> 4142 -> 8082 -> 7372 -> 8272");
    EXPECT_EQ(simulator.times(), 14);
}

TEST(ShaSimulate, Runx09)
{
    Board b;
    Move move;
    auto player = S_RED;
    b.set_pieces(rule_china_201);

    ShaSimulator simulator(b, player);
    EXPECT_FALSE(simulator.IsTrue());
    EXPECT_EQ(simulator.times(), 1);
}

TEST(ShaSimulate, Runx10)
{
    Board b;
    Move move;
    auto player = S_RED;
    b.set_pieces("4k4/4aRP2/r2Rba3/9/2b6/r3C4/9/2C6/4p4/5K1n1 w - - 0 1");

    ShaSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();

    EXPECT_TRUE(simulator.IsTrue());
    EXPECT_EQ(n->path(), "root -> 5859 -> 4959 -> 3739 -> 4839 -> 6858 -> 5958 -> 2252 -> 5748 -> 4454");
    EXPECT_EQ(simulator.times(), 11);
}

// 凡走子企图在下一着将军或连续将军以将死对方者，称为“杀”
// 停着不算杀
TEST(ShaSimulate, Runx11)
{
    Board b;
    Move move;
    auto player = S_RED;
    b.set_pieces("3ak4/4a1P2/9/9/9/9/9/9/9/4K4 w - - 0 1");

    ShaSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    // node->print(player);
    // 尽管红方平兵将死黑方，但红方平兵为停着，并不是将军，不算杀
    EXPECT_EQ(n->path(), "root");
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 不存在杀
TEST(ShaSimulate, Runx12)
{
    Board b;
    Move move;
    auto player = S_RED;
    b.set_pieces(rule_china_21);

    ShaSimulator simulator(b, player);
    EXPECT_FALSE(simulator.IsTrue());
    EXPECT_EQ(simulator.times(), 4);
}

// 参考图 25 改编
TEST(ShaSimulate, Runx13)
{
    Board b;
    auto player = S_RED;
    b.set_pieces("2bak1b2/4a2r1/4c1n2/p7p/2p2rpc1/4R4/P1PR2P1P/2N1C1N2/4A4/2BK1AB2 w - - 0 1");

    ShaSimulator simulator(b, player);
    EXPECT_FALSE(simulator.IsTrue());
    EXPECT_EQ(simulator.times(), 21);
}

// 图 09 改编
TEST(ShaSimulate, Runx14)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_09);

    ShaSimulator simulator(b, player);
    EXPECT_FALSE(simulator.IsTrue());
    EXPECT_EQ(simulator.times(), 48);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}