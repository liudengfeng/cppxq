#include <gtest/gtest.h>

#include "test_cases.hpp"
#include "rule2022.hpp"

using namespace rule2022;

// [==========] Running 38 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 38 tests from JDZSimulate
// [ RUN      ] JDZSimulate.Candsx01x1
// [       OK ] JDZSimulate.Candsx01x1 (22 ms)
// [ RUN      ] JDZSimulate.Candsx01x2
// [       OK ] JDZSimulate.Candsx01x2 (3 ms)
// [ RUN      ] JDZSimulate.Candsx01x3
// [       OK ] JDZSimulate.Candsx01x3 (13 ms)
// [ RUN      ] JDZSimulate.Candsx02x1
// [       OK ] JDZSimulate.Candsx02x1 (14 ms)
// [ RUN      ] JDZSimulate.Candsx02x2
// [       OK ] JDZSimulate.Candsx02x2 (10 ms)
// [ RUN      ] JDZSimulate.Candsx03x1
// [       OK ] JDZSimulate.Candsx03x1 (28 ms)
// [ RUN      ] JDZSimulate.Candsx04x1
// [       OK ] JDZSimulate.Candsx04x1 (5 ms)
// [ RUN      ] JDZSimulate.Candsx04x2
// [       OK ] JDZSimulate.Candsx04x2 (39 ms)
// [ RUN      ] JDZSimulate.Shax07
// [       OK ] JDZSimulate.Shax07 (2 ms)
// [ RUN      ] JDZSimulate.Shax242
// [       OK ] JDZSimulate.Shax242 (20 ms)
// [ RUN      ] JDZSimulate.Runx28
// [       OK ] JDZSimulate.Runx28 (14 ms)
// [ RUN      ] JDZSimulate.Runx234
// [       OK ] JDZSimulate.Runx234 (9 ms)
// [ RUN      ] JDZSimulate.Runx218
// [       OK ] JDZSimulate.Runx218 (54 ms)
// [ RUN      ] JDZSimulate.Runx02
// [       OK ] JDZSimulate.Runx02 (19 ms)
// [ RUN      ] JDZSimulate.Runx09x1
// [       OK ] JDZSimulate.Runx09x1 (104 ms)
// [ RUN      ] JDZSimulate.Runx09x2
// [       OK ] JDZSimulate.Runx09x2 (135 ms)
// [ RUN      ] JDZSimulate.Runx230x1
// [       OK ] JDZSimulate.Runx230x1 (75 ms)
// [ RUN      ] JDZSimulate.Runx214x1
// [       OK ] JDZSimulate.Runx214x1 (294 ms)
// [ RUN      ] JDZSimulate.Runx214x2
// [       OK ] JDZSimulate.Runx214x2 (335 ms)
// [ RUN      ] JDZSimulate.Runx03x1
// [       OK ] JDZSimulate.Runx03x1 (10 ms)
// [ RUN      ] JDZSimulate.Runx03x2
// [       OK ] JDZSimulate.Runx03x2 (19 ms)
// [ RUN      ] JDZSimulate.Runx212x1
// [       OK ] JDZSimulate.Runx212x1 (485 ms)
// [ RUN      ] JDZSimulate.Runx212x2
// [       OK ] JDZSimulate.Runx212x2 (58 ms)
// [ RUN      ] JDZSimulate.Runx05x1
// [       OK ] JDZSimulate.Runx05x1 (11 ms)
// [ RUN      ] JDZSimulate.Runx05x2
// [       OK ] JDZSimulate.Runx05x2 (22 ms)
// [ RUN      ] JDZSimulate.Runx05x3
// [       OK ] JDZSimulate.Runx05x3 (31 ms)
// [ RUN      ] JDZSimulate.Runx07x1
// [       OK ] JDZSimulate.Runx07x1 (43 ms)
// [ RUN      ] JDZSimulate.Runx07x2
// [       OK ] JDZSimulate.Runx07x2 (46 ms)
// [ RUN      ] JDZSimulate.Runx07x3
// [       OK ] JDZSimulate.Runx07x3 (47 ms)
// [ RUN      ] JDZSimulate.Runx13
// [       OK ] JDZSimulate.Runx13 (20 ms)
// [ RUN      ] JDZSimulate.Runx24x1
// [       OK ] JDZSimulate.Runx24x1 (7 ms)
// [ RUN      ] JDZSimulate.Runx24x2
// [       OK ] JDZSimulate.Runx24x2 (5 ms)
// [ RUN      ] JDZSimulate.Runx16
// [       OK ] JDZSimulate.Runx16 (10 ms)
// [ RUN      ] JDZSimulate.Runx17
// [       OK ] JDZSimulate.Runx17 (6 ms)
// [ RUN      ] JDZSimulate.Runx206x1
// [       OK ] JDZSimulate.Runx206x1 (18 ms)
// [ RUN      ] JDZSimulate.Runx206x2
// [       OK ] JDZSimulate.Runx206x2 (16 ms)
// [ RUN      ] JDZSimulate.Runx229
// [       OK ] JDZSimulate.Runx229 (11 ms)
// [ RUN      ] JDZSimulate.Runx230
// [       OK ] JDZSimulate.Runx230 (6 ms)
// [----------] 38 tests from JDZSimulate (2088 ms total)

// [----------] Global test environment tear-down
// [==========] 38 tests from 1 test suite ran. (2088 ms total)
// [  PASSED  ] 38 tests.

// ➡️ 抽将优先
TEST(JDZSimulate, Candsx01x1)
{
    Board b;
    b.set_pieces(rule_china_09);
    moveVec_t moves = {make_move("6472"), make_move("8070")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "抽将");
    Color player = S_BLACK;
    JdzSimulator simulator(b, player);
    b.SetPlayer(player);
    auto cands = simulator.get_cands(simulator.root, b);
    // fmt::print("{}\n", cands);
    EXPECT_EQ(cands.size(), 9);
    EXPECT_TRUE(contains(cands, make_move("6061")));
    EXPECT_TRUE(contains(cands, make_move("6062")));
}

// ➡️ 先行方将军候选中优先不被吃的部分 图2改编
TEST(JDZSimulate, Candsx01x2)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces("5a3/5k3/4P4/p7p/9/8P/P8/9/2nR5/2BAKAr2 b - - 0 1");
    // b.show_board();
    JdzSimulator simulator(b, player);

    auto node_ptr = simulator.root;
    auto board = simulator.init_board;
    board.SetPlayer(player);

    // 1. 将军
    auto cands0 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands0);
    EXPECT_EQ(cands0.size(), 1);

    node_ptr->expand(cands0);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 6050");

    board.SimulateMove(node_ptr->history.back());

    // 2. 应将
    auto cands1 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands1);
    EXPECT_EQ(cands1.size(), 1);

    node_ptr->expand(cands1);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 6050 -> 4041");

    board.SimulateMove(node_ptr->history.back());

    // 3. 将军时不被吃优先
    auto cands2 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands2);
    EXPECT_EQ(cands2.size(), 3);

    node_ptr->expand(cands2);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 6050 -> 4041 -> 5051");
}

// ➡️ 吃强子同时将军最优先
TEST(JDZSimulate, Candsx01x3)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_212);
    // b.show_board();

    moveVec_t moves = {make_move("1131"), make_move("3949"), make_move("3111")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    JdzSimulator simulator(b, player);

    auto node_ptr = simulator.root;
    auto board = simulator.init_board;
    board.SetPlayer(player);

    // 1. 将军
    auto cands0 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands0);
    EXPECT_EQ(cands0.size(), 2);

    node_ptr->expand(cands0);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 1119");

    board.SimulateMove(node_ptr->history.back());

    // 2. 应将
    auto cands1 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands1);
    EXPECT_EQ(cands1.size(), 2);

    node_ptr->expand(cands1);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 1119 -> 2629");

    board.SimulateMove(node_ptr->history.back());

    // 3. 吃强子同时将军优先
    auto cands2 = simulator.get_cands(node_ptr, board);
    // 前二者都可吃车
    // fmt::print("{}\n", cands2);
    EXPECT_EQ(cands2.size(), 12);

    node_ptr->expand(cands2);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 1119 -> 2629 -> 1929");
}

// ➡️ 早停
TEST(JDZSimulate, Candsx02x1)
{
    Board b;
    b.set_pieces(rule_china_28);
    // b.show_board();

    auto moves = {make_move("1929")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "早停");
    Color player = S_RED;
    JdzSimulator simulator(b, player);

    auto node_ptr = simulator.root;
    auto board = simulator.init_board;
    board.SetPlayer(player);

    // 1. 将军
    auto cands0 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands0);
    EXPECT_EQ(cands0.size(), 3);

    node_ptr->expand(cands0);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 2927");

    board.SimulateMove(node_ptr->history.back());

    // 2. 早停
    auto cands1 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands1);
    EXPECT_EQ(cands1.size(), 0);
}

// ➡️ 早停
TEST(JDZSimulate, Candsx02x2)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_02);

    moveVec_t moves = {make_move("7684"), make_move("8979"), make_move("8476")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }

    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto node_ptr = simulator.root;
    auto board = simulator.init_board;
    board.SetPlayer(player);

    // 1. 将军
    auto cands0 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands0);
    EXPECT_EQ(cands0.size(), 2);

    node_ptr->expand(cands0);
    node_ptr = node_ptr->children[1];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 7668");

    board.SimulateMove(node_ptr->history.back());

    // 2. 应将
    auto cands1 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands1);
    EXPECT_EQ(cands1.size(), 2);
    // 应将时吃优先
    EXPECT_EQ(cands1[0], make_move("2868"));

    node_ptr->expand(cands1);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 7668 -> 2868");

    board.SimulateMove(node_ptr->history.back());

    // 3. 吃
    auto cands2 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands2);
    EXPECT_EQ(cands2.size(), 1);
    // 将军导致的吃强子优先
    EXPECT_TRUE(cands2[0].is_eat());
    EXPECT_FALSE(cands2[0].is_check());
    EXPECT_EQ(cands2[0], make_move("7079"));

    node_ptr->expand(cands2);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 7668 -> 2868 -> 7079");

    // 4. 早停
    board.SimulateMove(node_ptr->history.back());
    auto cands3 = simulator.get_cands(node_ptr, board);
    EXPECT_EQ(cands3.size(), 0);
}

// ➡️ 剔除原本就存在的吃，即剔除非将军导致的吃
TEST(JDZSimulate, Candsx03x1)
{
    Board b;
    b.set_pieces(rule_china_09);
    moveVec_t moves = {make_move("6472"), make_move("8070")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board(true, "抽将");
    Color player = S_BLACK;
    JdzSimulator simulator(b, player);

    auto node_ptr = simulator.root;
    auto board = simulator.init_board;
    board.SetPlayer(player);

    // 1. 将军
    auto cands0 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands0);
    EXPECT_EQ(cands0.size(), 9);

    node_ptr->expand(cands0);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 6062");

    board.SimulateMove(node_ptr->history.back());

    // 2. 应将
    auto cands1 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands1);
    EXPECT_EQ(cands1.size(), 2);

    node_ptr->expand(cands1);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 6062 -> 4150");

    board.SimulateMove(node_ptr->history.back());

    // 3. 吃
    auto cands2 = simulator.get_cands(node_ptr, board);
    // board.show_board(true, node_ptr->path());
    // fmt::print("{}\n", cands2);
    EXPECT_EQ(cands2.size(), 3);
    // 先将后吃
    EXPECT_EQ(cands2[2], make_move("6222"));
}

// ➡️ 不得剔除吃未过河兵卒同时将军的候选
TEST(JDZSimulate, Candsx04x1)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_16);
    // b.show_board();

    moveVec_t moves = {make_move("7679"), make_move("5958"), make_move("7976")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();
    b.SetPlayer(player);

    JdzSimulator simulator(b, player);

    auto node_ptr = simulator.root;
    auto board = simulator.init_board;
    board.SetPlayer(player);

    // 1. 将军
    auto cands0 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands0);
    EXPECT_EQ(cands0.size(), 2);

    node_ptr->expand(cands0);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 7656");

    board.SimulateMove(node_ptr->history.back());
    // root -> 7656 -> 4857 -> 5646 -> 5748 -> 4636
    // 2. 应将
    auto cands1 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands1);
    EXPECT_EQ(cands1.size(), 1);

    node_ptr->expand(cands1);
    node_ptr = node_ptr->children[0];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 7656 -> 4857");

    board.SimulateMove(node_ptr->history.back());

    // 3. 吃未过河的兵卒同时将军
    auto cands2 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands2);
    EXPECT_EQ(cands2.size(), 5);
    Move expected = make_move("5646");
    EXPECT_TRUE(contains(cands2, expected));
}

// ➡️ 应将顺序
// ➡️ 先手将军后不得使用期初本已经存在的吃无根子
TEST(JDZSimulate, Candsx04x2)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_212);
    // b.show_board();

    moveVec_t moves = {make_move("1131"), make_move("3949"), make_move("3111")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();
    b.SetPlayer(player);

    JdzSimulator simulator(b, player);

    auto node_ptr = simulator.root;
    auto board = simulator.init_board;
    board.SetPlayer(player);

    // 1. 将军
    auto cands0 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands0);
    EXPECT_EQ(cands0.size(), 6);

    node_ptr->expand(cands0);
    node_ptr = node_ptr->children[4];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 4223");

    board.SimulateMove(node_ptr->history.back());

    // 2. 应将
    auto cands1 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands1);
    EXPECT_EQ(cands1.size(), 11);
    // 应将优先让对手无法继续将军
    EXPECT_FALSE(cands1[0] == make_move("4322"));

    node_ptr->expand(cands1);
    node_ptr = node_ptr->children[5];
    // node_ptr->view_detail(player);
    EXPECT_EQ(node_ptr->path(), "root -> 4223 -> 4322");

    board.SimulateMove(node_ptr->history.back());

    // 3. 先手将军后不得使用期初本已经存在的吃
    auto cands2 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands2);
    EXPECT_EQ(cands2.size(), 2);
    Move expected = make_move("6947");
    EXPECT_FALSE(contains(cands2, expected));
}

// ➡️ 被杀
TEST(JDZSimulate, Shax07)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_07);
    JdzSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    //                 ✂️
    // root -> 8880 -> 5850
    //                 反杀
    // 如黑方继续吃士，红方有杀
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_EQ(n->path(), "root");
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 剪裁导致自杀部分
TEST(JDZSimulate, Shax242)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_242);
    JdzSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    //                                                 ✂️
    // root -> 0200 -> 4130 -> 2720 -> 3041 -> 2050 -> 4130
    //                                                 非吃
    // 如黑方继续吃士，红方有杀
    EXPECT_EQ(simulator.times(), 3);
    EXPECT_EQ(n->path(), "root -> 0200 -> 4130 -> 2720 -> 3041 -> 2050");
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 早停
TEST(JDZSimulate, Runx28)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_28);
    // b.show_board();

    auto moves = {make_move("1929")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 2927");
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_TRUE(simulator.IsTrue());
}

// 参考图34改编
// ➡️ 吃车优先于将军
TEST(JDZSimulate, Runx234)
{
    Board b;
    b.set_pieces("3k1ab2/4a4/4b4/2p6/6p2/3r5/6P1P/4BA3/2C1K4/7R1 b - - 0 1");
    // b.show_board();

    Color player = S_BLACK;
    JdzSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 3431 -> 4140 -> 3130 -> 4041 -> 3070");
    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
    EXPECT_FALSE(n->history.front().info.is_jointed);
}

// ➡️ 吃车优先于将军
// ➡️ 早停
TEST(JDZSimulate, Runx218)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_218);

    auto moves = {make_move("4030"), make_move("1242"), make_move("3040"), make_move("4212")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();
    JdzSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    // 最优路径，避免被杀
    EXPECT_EQ(n->path(), "root -> 3343 -> 4030 -> 4348");
    EXPECT_EQ(simulator.times(), 15);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 早停
// root -> 7668 -> 4939 -> 7079 -> 2868
//                              ^  早停
TEST(JDZSimulate, Runx02)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_02);

    moveVec_t moves = {make_move("7684"), make_move("8979"), make_move("8476")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }

    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 7668 -> 2868 -> 7079");
    EXPECT_EQ(simulator.times(), 3);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 优先抽吃
// ➡️ 将军导致的吃优先
TEST(JDZSimulate, Runx09x1)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_09);

    moveVec_t moves = {make_move("6472"), make_move("8070")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 6062 -> 4150 -> 6222");

    EXPECT_EQ(simulator.times(), 8);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 优先抽吃
// ➡️ 将军导致的吃优先
TEST(JDZSimulate, Runx09x2)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_09);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 6062 -> 4150 -> 6222");

    EXPECT_EQ(simulator.times(), 17);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 图30 改编兑子模拟
TEST(JDZSimulate, Runx230x1)
{
    Board b;
    b.set_pieces("2bakab2/9/4c3c/pCp1nr2p/7n1/2P6/P3P1P1P/4C1N2/9/1RBAKAB2 w - - 0 1");
    // b.show_board();

    Color player = S_RED;
    JdzSimulator simulator(b, player);
    Coord tgt{4, 6};
    simulator.set_target(tgt);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 4246");
    EXPECT_EQ(simulator.times(), 20);
    EXPECT_TRUE(simulator.IsTrue());
}

// 早停
TEST(JDZSimulate, Runx214x1)
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

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 6030 -> 4150 -> 3000");

    EXPECT_EQ(simulator.times(), 53);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(JDZSimulate, Runx214x2)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_214);
    moveVec_t moves = {make_move("8261")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();

    JdzSimulator simulator(b, player);
    // 可得士
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 6030");

    EXPECT_EQ(simulator.times(), 65);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 连续将军得子
TEST(JDZSimulate, Runx03x1)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_03);

    moveVec_t moves = {make_move("4260"), make_move("7161")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 6160 -> 4150 -> 6050 -> 4041 -> 5051 -> 4140 -> 5131");
    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 断根捉子：如先吃，模拟是否能够通过将军得子吃回
// ➡️ 提高通过标准，防止早停
// ➡️ 最大最小算法
// ➡️ 折扣率设定：过高折扣率会导致无法区分弱子价值
TEST(JDZSimulate, Runx03x2)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_03);

    moveVec_t moves = {make_move("3121")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 7170 -> 4150 -> 7050 -> 4041 -> 5051 -> 4140 -> 5121");
    EXPECT_EQ(simulator.times(), 5);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(JDZSimulate, Runx212x1)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_212);
    // b.show_board();

    moveVec_t moves = {make_move("1131"), make_move("3949"), make_move("3111")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 1119 -> 4839 -> 1916 -> 2629 -> 1646");
    EXPECT_EQ(simulator.times(), 82);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(JDZSimulate, Runx212x2)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_212);
    // b.show_board();

    moveVec_t moves = {make_move("1131"), make_move("3949"), make_move("3111"), make_move("4939")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 4230 -> 1141 -> 4641 -> 4041");
    EXPECT_EQ(simulator.times(), 13);
    EXPECT_TRUE(simulator.IsTrue());
    // n->view_tree(player);
}

// ➡️ 超出最大模拟次数限制 800 一律视同无法得子
TEST(JDZSimulate, Runx212x3)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_212);
    // b.show_board();

    moveVec_t moves = {make_move("1131"), make_move("3949"), make_move("3111")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");
    // 不设限制 耗时 154013 ms
    // root -> 4223 -> 4322 -> 2344 -> 1141 -> 4641 -> 3041
    EXPECT_EQ(simulator.times(), MAX_NUM_OF_MOCK);
    EXPECT_FALSE(simulator.IsTrue());
    // n->view_tree(player);
}

// ➡️ 可直接吃士，但无法将军得子
// ➡️ 剪除失误导致被杀
TEST(JDZSimulate, Runx05x1)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_05);

    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    // 未通过
    EXPECT_EQ(n->path(), "root");
    EXPECT_EQ(simulator.times(), 5);
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 自杀
// ➡️ 失误被将死
TEST(JDZSimulate, Runx05x2)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_05);

    moveVec_t moves = {make_move("2924")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }

    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    // 将军得士
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 2444 -> 4858 -> 4454 -> 5848 -> 5459");
    EXPECT_EQ(simulator.times(), 10);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 图5改编 去掉保护红炮的士
// ➡️ 无法实现先得后失类型的得子
TEST(JDZSimulate, Runx05x3)
{
    Board b;
    Color player = S_RED;
    b.set_pieces("2R2a3/4k4/3a5/9/8p/9/1p1rpn3/3CB4/9/2B1KA3 w - - 0 1");

    moveVec_t moves = {make_move("2924")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }

    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    //    root -> 2444 -> 4858 -> 3237 -> 4342 -> 2042 -> 3337 v=0 pass=false
    EXPECT_EQ(n->path(), "root");
    EXPECT_EQ(simulator.times(), 15);
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 处理重复局面
// ➡️ 不可直接使用期初吃无根子的移动
TEST(JDZSimulate, Runx07x1)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces("8R/3ka4/3a5/9/9/4p4/7c1/4B1r2/4A4/3A1KB2 w - - 0 1");

    b.SetPlayer(player);
    // b.show_board();

    JdzSimulator simulator(b, player);

    // 黑方可通过将军得`相`
    auto n = simulator.ReasonablePath();
    // node->print(player);
    EXPECT_EQ(n->path(), "root -> 7370 -> 5051 -> 6260");
    EXPECT_TRUE(simulator.IsTrue());
    EXPECT_EQ(simulator.times(), 14);
}

TEST(JDZSimulate, Runx07x2)
{
    Board b;
    b.set_pieces("7R1/3ka4/3a5/9/9/4p4/8c/4B1r2/4A4/3A1KB2 w - - 0 1");

    // b.show_board();

    Color player = S_BLACK;
    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");
    // 无法通过将军得子
    EXPECT_EQ(simulator.times(), 17);
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 排除吃未过河的兵、卒
TEST(JDZSimulate, Runx07x3)
{
    Board b;
    b.set_pieces(rule_china_202);
    moveVec_t moves = {make_move("5041"), make_move("6160"), make_move("4150"), make_move("6061")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();

    auto player = S_BLACK;
    JdzSimulator simulator(b, player);

    // 黑方可通过将军得`相`
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 8280 -> 5041 -> 8020");
    EXPECT_TRUE(simulator.IsTrue());
    EXPECT_EQ(simulator.times(), 16);
}

// ➡️ 修复重复将军导致输棋
TEST(JDZSimulate, Runx13)
{
    Board b;
    b.set_pieces(rule_china_13);
    // b.show_board();

    moveVec_t moves = {make_move("4636"), make_move("3949"), make_move("3646")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();

    Color player = S_BLACK;
    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");
    EXPECT_EQ(simulator.times(), 7);
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 先失后得不能算得子
TEST(JDZSimulate, Runx24x1)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_24);

    auto moves1 = {make_move("8589")};
    for (auto m : moves1)
    {
        b.DoMove(m);
    }

    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");
    EXPECT_EQ(simulator.times(), 5);

    // 过河兵换马不算得子
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 可吃回时即使得子也不得早停
// ➡️ 送吃
// ➡️ 将军被吃
// root -> 8545 -> 5848 -> 4548 -> 4948
TEST(JDZSimulate, Runx24x2)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_24);

    auto moves = {make_move("8589"), make_move("4858"), make_move("8985")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }

    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 8545 -> 5848 -> 2939 -> 4939 -> 4548");

    EXPECT_EQ(simulator.times(), 2);

    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 抽将
// ➡️ 检验候选、早听案例
// ➡️ 兄弟节点已经得车，候选为空
// ➡️ 吃未过河兵卒同时将军
TEST(JDZSimulate, Runx16)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_16);
    // b.show_board();

    moveVec_t moves = {make_move("7679"), make_move("5958"), make_move("7976")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();
    b.SetPlayer(player);
    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(simulator.times(), 3);
    EXPECT_EQ(n->path(), "root -> 7656 -> 4857 -> 5646 -> 5748 -> 4636");
    EXPECT_TRUE(simulator.IsTrue());
    // 所动之子为车或炮，车、炮同时将军，也视同其他子将军，便于判定联合捉
    EXPECT_TRUE(n->history.front().info.is_jointed);
}

// 图 17 改编
TEST(JDZSimulate, Runx17)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_17);
    // 对手先吃
    auto moves = {make_move("1718"), make_move("3837"), make_move("1817"), make_move("2717")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    // root -> 1917 -> 3738 -> 1777
    EXPECT_EQ(n->path(), "root -> 1917 -> 3738 -> 1777");
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 如后手失误导致被杀，回退二步
TEST(JDZSimulate, Runx206x1)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_206);

    auto m1 = make_move("0907");

    b.DoMove(m1);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    // 将军得双士
    EXPECT_EQ(n->path(), "root -> 0747 -> 3948 -> 5859 -> 4939 -> 4748");
    EXPECT_EQ(simulator.times(), 4);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 前端已经得子，如尾部二项或三项净收益为零则剪除
TEST(JDZSimulate, Runx206x2)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_206);

    b.SetPlayer(player);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    // 将军得双士
    EXPECT_EQ(n->path(), "root -> 5859 -> 4948 -> 0939");
    EXPECT_EQ(simulator.times(), 5);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 最终路径
TEST(JDZSimulate, Runx229)
{
    Board b;
    Color player = S_BLACK;
    b.set_pieces(rule_china_229);

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 4342 -> 6042 -> 5313");
    EXPECT_EQ(simulator.times(), 4);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 非得不偿失的得子
TEST(JDZSimulate, Runx230)
{
    Board b;
    Color player = S_RED;
    b.set_pieces(rule_china_230);
    // b.show_board();

    moveVec_t moves = {make_move("5969"), make_move("4757"), make_move("6959")};
    for (auto m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();

    JdzSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 5848 -> 5747 -> 5956");
    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}