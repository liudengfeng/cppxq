#include <gtest/gtest.h>

#include "test_cases.hpp"
#include "rule2022.hpp"

using namespace rule2022;

// [==========] Running 33 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 33 tests from ChiSimulate
// [ RUN      ] ChiSimulate.Candsx01
// [       OK ] ChiSimulate.Candsx01 (0 ms)
// [ RUN      ] ChiSimulate.Candsx02
// [       OK ] ChiSimulate.Candsx02 (0 ms)
// [ RUN      ] ChiSimulate.Candsx03
// [       OK ] ChiSimulate.Candsx03 (0 ms)
// [ RUN      ] ChiSimulate.Candsx04
// [       OK ] ChiSimulate.Candsx04 (0 ms)
// [ RUN      ] ChiSimulate.Candsx05
// [       OK ] ChiSimulate.Candsx05 (0 ms)
// [ RUN      ] ChiSimulate.Runx00x1
// [       OK ] ChiSimulate.Runx00x1 (1 ms)
// [ RUN      ] ChiSimulate.Runx00x2
// [       OK ] ChiSimulate.Runx00x2 (7 ms)
// [ RUN      ] ChiSimulate.Runx01x1
// [       OK ] ChiSimulate.Runx01x1 (2 ms)
// [ RUN      ] ChiSimulate.Runx01x2
// [       OK ] ChiSimulate.Runx01x2 (57 ms)
// [ RUN      ] ChiSimulate.Runx02x1
// [       OK ] ChiSimulate.Runx02x1 (11 ms)
// [ RUN      ] ChiSimulate.Runx02x2
// [       OK ] ChiSimulate.Runx02x2 (0 ms)
// [ RUN      ] ChiSimulate.Runx03x1
// [       OK ] ChiSimulate.Runx03x1 (1 ms)
// [ RUN      ] ChiSimulate.Runx03x2
// [       OK ] ChiSimulate.Runx03x2 (8 ms)
// [ RUN      ] ChiSimulate.Runx04
// [       OK ] ChiSimulate.Runx04 (3 ms)
// [ RUN      ] ChiSimulate.Runx05
// [       OK ] ChiSimulate.Runx05 (3 ms)
// [ RUN      ] ChiSimulate.Runx06x1
// [       OK ] ChiSimulate.Runx06x1 (11 ms)
// [ RUN      ] ChiSimulate.Runx06x2
// [       OK ] ChiSimulate.Runx06x2 (7 ms)
// [ RUN      ] ChiSimulate.Runx07
// [       OK ] ChiSimulate.Runx07 (4 ms)
// [ RUN      ] ChiSimulate.Runx08
// [       OK ] ChiSimulate.Runx08 (1 ms)
// [ RUN      ] ChiSimulate.Runx25x1
// [       OK ] ChiSimulate.Runx25x1 (54 ms)
// [ RUN      ] ChiSimulate.Runx25x2
// [       OK ] ChiSimulate.Runx25x2 (135 ms)
// [ RUN      ] ChiSimulate.Runx25x3
// [       OK ] ChiSimulate.Runx25x3 (23 ms)
// [ RUN      ] ChiSimulate.Runx216x1
// [       OK ] ChiSimulate.Runx216x1 (3 ms)
// [ RUN      ] ChiSimulate.Runx216x2
// [       OK ] ChiSimulate.Runx216x2 (7 ms)
// [ RUN      ] ChiSimulate.Runx216x3
// [       OK ] ChiSimulate.Runx216x3 (5 ms)
// [ RUN      ] ChiSimulate.Runx11
// [       OK ] ChiSimulate.Runx11 (3 ms)
// [ RUN      ] ChiSimulate.Runx12
// [       OK ] ChiSimulate.Runx12 (3 ms)
// [ RUN      ] ChiSimulate.Runx215x1
// [       OK ] ChiSimulate.Runx215x1 (23 ms)
// [ RUN      ] ChiSimulate.Runx215x2
// [       OK ] ChiSimulate.Runx215x2 (18 ms)
// [ RUN      ] ChiSimulate.Runx215x3
// [       OK ] ChiSimulate.Runx215x3 (24 ms)
// [ RUN      ] ChiSimulate.Runx14
// [       OK ] ChiSimulate.Runx14 (5 ms)
// [ RUN      ] ChiSimulate.Runx223
// [       OK ] ChiSimulate.Runx223 (31 ms)
// [ RUN      ] ChiSimulate.Runx239
// [       OK ] ChiSimulate.Runx239 (5 ms)
// [----------] 33 tests from ChiSimulate (472 ms total)

// [----------] Global test environment tear-down
// [==========] 33 tests from 1 test suite ran. (472 ms total)
// [  PASSED  ] 33 tests.

// ➡️ 首着非将
TEST(ChiSimulate, Candsx01)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_03);
    moveVec_t moves = {make_move("4260"), make_move("7161")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto root = simulator.root;
    auto board = simulator.init_board;

    auto cands0 = simulator.get_cands(root, board);

    // fmt::print("{}\n", cands0);

    EXPECT_EQ(cands0.size(), 0);
}

TEST(ChiSimulate, Candsx02)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_04);
    moveVec_t moves = {make_move("5635"), make_move("8765"), make_move("3556")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto root = simulator.root;
    auto board = simulator.init_board;

    auto cands0 = simulator.get_cands(root, board);

    // fmt::print("{}\n", cands0);

    EXPECT_EQ(cands0.size(), 2);
    auto expected1 = make_move("5644");
    auto expected2 = make_move("8525");
    EXPECT_EQ(cands0[0], expected1);
    EXPECT_EQ(cands0[1], expected2);
}

// ➡️ 首着不得为将，即使吃也不行
TEST(ChiSimulate, Candsx03)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_02);
    moveVec_t moves = {make_move("7684"), make_move("8979")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto root = simulator.root;
    auto board = simulator.init_board;

    auto cands0 = simulator.get_cands(root, board);

    // fmt::print("{}\n", cands0);

    EXPECT_EQ(cands0.size(), 1);
    auto expected1 = make_move("7970");
    auto expected = make_move("1914");
    // 7970 为将         排除
    // 2723 吃未过河的兵 排除
    EXPECT_FALSE(contains(cands0, expected1));
    EXPECT_TRUE(contains(cands0, expected));
}

// ➡️ 首着不得为将，即使吃也不行
TEST(ChiSimulate, Candsx04)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_206);
    moveVec_t moves = {make_move("0907")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto root = simulator.root;
    auto board = simulator.init_board;

    auto cands0 = simulator.get_cands(root, board);

    // 5859 为将         排除
    EXPECT_EQ(cands0.size(), 0);
}

// ➡️ 从第二着开始，有杀即返回
TEST(ChiSimulate, Candsx05)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_05);

    // b.show_board();
    ChiSimulator simulator(b, player);

    auto node_ptr = simulator.root;
    auto board = simulator.init_board;

    auto cands0 = simulator.get_cands(node_ptr, board);
    // fmt::print("{}\n", cands0);
    node_ptr->expand(cands0);

    node_ptr = node_ptr->children[0];
    // node_ptr->print(player);

    board.SimulateMove(node_ptr->history.back());
    auto cands = simulator.get_cands(node_ptr, board);

    // fmt::print("{}\n", cands);

    EXPECT_EQ(cands.size(), 1);
    auto expected = make_move("5361");
    EXPECT_EQ(cands[0], expected);
}

// ➡️ 一旦吃即被杀
TEST(ChiSimulate, Runx00x1)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces("2bak1c2/4aRN2/4b4/9/9/7r1/3p5/2n1B4/9/2B1KA2C b - - 0 1");
    moveVec_t moves = {make_move("7484")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");

    EXPECT_EQ(simulator.times(), 1);
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 截尾
// ➡️ 一步杀
TEST(ChiSimulate, Runx00x2)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces("2bak1c2/4aRNr1/4b4/9/9/9/3pp4/2n1B4/9/2B1KA2C b - - 0 1");
    moveVec_t moves = {make_move("7888")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");

    EXPECT_EQ(simulator.times(), 3);
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 互吃
TEST(ChiSimulate, Runx01x1)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_04);
    moveVec_t moves = {make_move("5635"), make_move("8765"), make_move("3556")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 8525 -> 4725 -> 5644");
    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
}

// 参考图31改编 以浮动价值的兵交换象，不算得子
// ➡️ 合理截断点案例
// ➡️ 送吃
TEST(ChiSimulate, Runx01x2)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces("R2ck4/4a4/4b4/4r4/2c3b1P/6N2/4C4/4B4/9/2BAKA3 b - - 0 1");
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 2585 -> 4347 -> 6547 -> 6485");

    EXPECT_EQ(simulator.times(), 24);
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 指定目标坐标
TEST(ChiSimulate, Runx02x1)
{
    Board b;
    b.set_pieces(rule_china_05);

    // b.show_board();

    Coord target{5, 9};
    auto player = S_RED;
    ChiSimulator simulator(b, player);
    simulator.set_target(target);
    auto n = simulator.ReasonablePath();
    // 裁剪
    //                 ✂️
    // root -> 2959 -> 4342 -> 2042 -> 5332 -> 4132 -> 3332
    //                  ^
    EXPECT_EQ(n->path(), "root -> 2959");
    EXPECT_EQ(simulator.times(), 5);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 被杀
TEST(ChiSimulate, Runx02x2)
{
    Board b;
    b.set_pieces(rule_china_05);

    // b.show_board();

    Coord target{3, 7};
    auto player = S_RED;
    ChiSimulator simulator(b, player);
    simulator.set_target(target);
    auto n = simulator.ReasonablePath();

    // 被杀
    EXPECT_EQ(n->path(), "root");
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 第一步将军，进行将得子模拟
TEST(ChiSimulate, Runx03x1)
{
    Board b;
    b.set_pieces(rule_china_30);
    moveVec_t moves = {make_move("1612"), make_move("5256"), make_move("1216"), make_move("2746")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto player = S_RED;
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");

    EXPECT_EQ(simulator.times(), 1);
    EXPECT_FALSE(simulator.IsTrue());
}

// 图30改编：第一步非将军
TEST(ChiSimulate, Runx03x2)
{
    Board b;
    b.set_pieces("2b1kab2/4a4/2n1c3c/pCp1Nr2p/7n1/2P6/P3P1P1P/4C1N2/9/1RBAKAB2 b - - 0 1");
    moveVec_t moves = {make_move("2746")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto player = S_RED;
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 4246");

    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 利用杀得子
// ➡️ 模拟最终路径处理：不影响得子时，裁除尾部兑
TEST(ChiSimulate, Runx04)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_205);
    // b.show_board();

    moveVec_t moves = {make_move("0609"), make_move("1619"), make_move("0908")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }

    // b.show_board();
    ChiSimulator simulator(b, player);
    Coord tgt{6, 5};
    simulator.set_target(tgt);
    auto n = simulator.ReasonablePath();
    // 保留后面的兑
    // EXPECT_EQ(n->path(), "root -> 7565 -> 1565 -> 5765 -> 4765");
    EXPECT_EQ(n->path(), "root -> 7565");
    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
    EXPECT_TRUE(n->history.front().info.is_jointed);
}

TEST(ChiSimulate, Runx05)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_23);
    moveVec_t moves = {make_move("2122"), make_move("1211")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_FALSE(simulator.IsTrue());
}

TEST(ChiSimulate, Runx06x1)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_225);
    moveVec_t moves = {make_move("4252"), make_move("5949"), make_move("5242")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 4447");

    EXPECT_EQ(simulator.times(), 3);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(ChiSimulate, Runx06x2)
{
    // 去掉黑底士
    Board b;
    auto player = S_RED;
    b.set_pieces("2b1k1b2/4a2r1/4c1n2/p7p/2p2rpc1/4R4/P1PR2P1P/2N2CN2/4A4/2BK1AB2 w - - 0 1");
    moveVec_t moves = {make_move("5242")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 4447");

    EXPECT_EQ(simulator.times(), 3);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(ChiSimulate, Runx07)
{
    Board b;
    b.set_pieces(rule_china_201);

    moveVec_t moves = {make_move("7554")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();

    auto player = S_RED;
    ChiSimulator simulator(b, player);
    // Coord tgt{4, 7};
    // simulator.set_target(tgt);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 5547");
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_TRUE(simulator.IsTrue());
    EXPECT_TRUE(n->history.front().info.is_jointed);
}

// ➡️ 限定第一步非将军
TEST(ChiSimulate, Runx08)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_211);
    moveVec_t moves = {make_move("4050"), make_move("4454")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_FALSE(simulator.IsTrue());
}

// ➡️ 指定目标
TEST(ChiSimulate, Runx25x1)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_25);

    auto player = S_RED;
    moved = make_move("3435");
    b.DoMove(moved);
    // b.show_board();
    ChiSimulator simulator(b, player);
    Coord tgt{3, 9};
    simulator.set_target(tgt);
    auto n = simulator.ReasonablePath();
    // EXPECT_EQ(n->path(), "root -> 3339 -> 4839 -> 3539 -> 4948 -> 5258");
    // EXPECT_EQ(simulator.times(), 62);
    EXPECT_EQ(n->path(), "root -> 3339 -> 4839 -> 5258");
    EXPECT_EQ(simulator.times(), 9);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 尾部剪裁
TEST(ChiSimulate, Runx25x2)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_25);

    auto player = S_BLACK;
    moveVec_t moves = {make_move("3435"), make_move("5567"), make_move("3534"), make_move("6755")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 5534");
    EXPECT_EQ(simulator.times(), 25);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 综合案例
// ➡️ 计算含输赢的净收益
TEST(ChiSimulate, Runx25x3)
{
    Board b;
    Move moved;
    b.set_pieces(rule_china_25);

    auto player = S_RED;
    moved = make_move("3435");
    b.DoMove(moved);
    // b.show_board();
    ChiSimulator simulator(b, player);

    auto n = simulator.ReasonablePath();
    // EXPECT_EQ(n->path(), "root -> 3339 -> 4839 -> 3539 -> 4948 -> 5258");
    // EXPECT_EQ(simulator.times(), 65);
    EXPECT_EQ(n->path(), "root -> 5258");
    EXPECT_EQ(simulator.times(), 3);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 等值交换
TEST(ChiSimulate, Runx216x1)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_216);
    moveVec_t moves = {make_move("4636")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    // 根节点下优先相关吃
    EXPECT_EQ(n->path(), "root -> 3637");
    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
}

// 26.1.1 走动帅(将)、兵(卒)后与其他子配合同时产生“捉”或走动后其他子产生新的“捉”，按“捉”处理(见图15、参考图16)。
// 模拟操作判定：等值交换时是否得子
// 结合裁判细则，本例应判`否`
TEST(ChiSimulate, Runx216x2)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_216);
    moveVec_t moves = {make_move("4636"), make_move("4535")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    // 各吃各子的捉子
    EXPECT_EQ(n->path(), "root -> 5352 -> 3637 -> 3537 -> 5652");
    EXPECT_EQ(simulator.times(), 5);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 指定开始坐标
TEST(ChiSimulate, Runx216x3)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_216);
    moveVec_t moves = {make_move("4636"), make_move("4535")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    Coord target{5, 2};
    simulator.set_target(target);
    auto n = simulator.ReasonablePath();
    // 各吃各子的捉子
    EXPECT_EQ(n->path(), "root -> 5352 -> 3637 -> 3537 -> 5652");
    EXPECT_EQ(simulator.times(), 4);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(ChiSimulate, Runx11)
{
    Board b;
    b.set_pieces(rule_china_22);
    moveVec_t moves = {make_move("3646")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto player = S_RED;
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    // 做“根”子完整互吃后价值相当按“捉”
    EXPECT_EQ(n->path(), "root -> 4644 -> 1816");
    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
}

// 被“牵”子捉子
TEST(ChiSimulate, Runx12)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_227);
    moveVec_t moves = {make_move("3626")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 2621 -> 5606");
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(ChiSimulate, Runx215x1)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_215);
    moveVec_t moves = {make_move("3331")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    // 剔除尾部兑
    EXPECT_EQ(n->path(), "root -> 3171");
    EXPECT_EQ(simulator.times(), 1);
    EXPECT_TRUE(simulator.IsTrue());
    // 路径裁剪兑后，如捉目标不能离线则为联合捉
    EXPECT_FALSE(n->history.front().info.is_jointed);
}

TEST(ChiSimulate, Runx215x2)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_215);
    moveVec_t moves = {make_move("3331"), make_move("7173")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 6562");
    EXPECT_EQ(simulator.times(), 3);
    EXPECT_TRUE(simulator.IsTrue());
}

TEST(ChiSimulate, Runx215x3)
{
    Board b;
    auto player = S_RED;
    b.set_pieces(rule_china_215);
    moveVec_t moves = {make_move("3331"), make_move("7173"), make_move("3133")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root");
    EXPECT_EQ(simulator.times(), 5);
    EXPECT_FALSE(simulator.IsTrue());
}

TEST(ChiSimulate, Runx14)
{
    Board b;
    b.set_pieces(rule_china_213);

    moveVec_t moves = {make_move("1232"), make_move("1333")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();

    auto player = S_BLACK;
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 8030 -> 4130 -> 3332");
    EXPECT_EQ(simulator.times(), 3);
    EXPECT_TRUE(simulator.IsTrue());
}

// ➡️ 合理截断点案例
// ➡️ 送吃
TEST(ChiSimulate, Runx223)
{
    Board b;
    b.set_pieces(rule_china_223);

    moveVec_t moves = {make_move("3638"), make_move("2925"), make_move("3836")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();

    auto player = S_RED;
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    // 剔除尾部兑
    EXPECT_EQ(n->path(), "root -> 2425");
    EXPECT_EQ(simulator.times(), 8);
    EXPECT_TRUE(simulator.IsTrue());
    EXPECT_FALSE(n->history.front().info.is_jointed);
}

TEST(ChiSimulate, Runx239)
{
    Board b;
    b.set_pieces(rule_china_239);

    moveVec_t moves = {make_move("6766"), make_move("4654"), make_move("6667")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();

    auto player = S_RED;
    ChiSimulator simulator(b, player);
    auto n = simulator.ReasonablePath();
    EXPECT_EQ(n->path(), "root -> 7858");
    EXPECT_EQ(simulator.times(), 2);
    EXPECT_TRUE(simulator.IsTrue());
    EXPECT_TRUE(n->history.front().info.is_jointed);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}