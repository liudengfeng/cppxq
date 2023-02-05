#include <gtest/gtest.h>

#include "test_cases.hpp"
#include "rule2022.hpp"

using namespace rule2022;

// [==========] Running 28 tests from 1 test suite.
// [----------] Global test environment set-up.
// [----------] 28 tests from TestRuleUtils
// [ RUN      ] TestRuleUtils.Runx01x1
// [       OK ] TestRuleUtils.Runx01x1 (0 ms)
// [ RUN      ] TestRuleUtils.Runx01x2
// [       OK ] TestRuleUtils.Runx01x2 (0 ms)
// [ RUN      ] TestRuleUtils.Runx01x3
// [       OK ] TestRuleUtils.Runx01x3 (0 ms)
// [ RUN      ] TestRuleUtils.Runx02x1
// [       OK ] TestRuleUtils.Runx02x1 (0 ms)
// [ RUN      ] TestRuleUtils.Runx02x2
// [       OK ] TestRuleUtils.Runx02x2 (0 ms)
// [ RUN      ] TestRuleUtils.Runx02x3
// [       OK ] TestRuleUtils.Runx02x3 (0 ms)
// [ RUN      ] TestRuleUtils.Runx02x4
// [       OK ] TestRuleUtils.Runx02x4 (0 ms)
// [ RUN      ] TestRuleUtils.TestEatJustCrossRiverPawnx1
// [       OK ] TestRuleUtils.TestEatJustCrossRiverPawnx1 (0 ms)
// [ RUN      ] TestRuleUtils.TestEatJustCrossRiverPawnx2
// [       OK ] TestRuleUtils.TestEatJustCrossRiverPawnx2 (0 ms)
// [ RUN      ] TestRuleUtils.TestEatJustCrossRiverPawnx3
// [       OK ] TestRuleUtils.TestEatJustCrossRiverPawnx3 (0 ms)
// [ RUN      ] TestRuleUtils.TestEatJustCrossRiverPawnx4
// [       OK ] TestRuleUtils.TestEatJustCrossRiverPawnx4 (0 ms)
// [ RUN      ] TestRuleUtils.TestEatJustCrossRiverPawnx5
// [       OK ] TestRuleUtils.TestEatJustCrossRiverPawnx5 (0 ms)
// [ RUN      ] TestRuleUtils.TestEatJustCrossRiverPawnx6
// [       OK ] TestRuleUtils.TestEatJustCrossRiverPawnx6 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix01x1
// [       OK ] TestRuleUtils.TestDezix01x1 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix01x2
// [       OK ] TestRuleUtils.TestDezix01x2 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x1
// [       OK ] TestRuleUtils.TestDezix02x1 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x2
// [       OK ] TestRuleUtils.TestDezix02x2 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x3
// [       OK ] TestRuleUtils.TestDezix02x3 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x4
// [       OK ] TestRuleUtils.TestDezix02x4 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x5x1
// [       OK ] TestRuleUtils.TestDezix02x5x1 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x6
// [       OK ] TestRuleUtils.TestDezix02x6 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x7
// [       OK ] TestRuleUtils.TestDezix02x7 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x8
// [       OK ] TestRuleUtils.TestDezix02x8 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x9x1
// [       OK ] TestRuleUtils.TestDezix02x9x1 (0 ms)
// [ RUN      ] TestRuleUtils.TestDezix02x9x2
// [       OK ] TestRuleUtils.TestDezix02x9x2 (0 ms)
// [ RUN      ] TestRuleUtils.Pawnx01x1
// [       OK ] TestRuleUtils.Pawnx01x1 (1 ms)
// [ RUN      ] TestRuleUtils.Pawnx01x2
// [       OK ] TestRuleUtils.Pawnx01x2 (1 ms)
// [ RUN      ] TestRuleUtils.CanNotOfflinex01x1
// [       OK ] TestRuleUtils.CanNotOfflinex01x1 (0 ms)
// [----------] 28 tests from TestRuleUtils (15 ms total)

// [----------] Global test environment tear-down
// [==========] 28 tests from 1 test suite ran. (15 ms total)
// [  PASSED  ] 28 tests.

// 截取部分路径
TEST(TestRuleUtils, Runx01x1)
{
    moveVec_t hist = {
        make_move("2959"),
        make_move("4342"),
        make_move("3237"),
        make_move("3337"),

        make_move("2042"),
        make_move("5341"),
        make_move("4041")};

    auto p0 = get_part_of_history(hist, 0, 0);
    EXPECT_EQ(p0.size(), 0);

    auto p1 = get_part_of_history(hist, 3, 0);
    EXPECT_EQ(p1.size(), 3);
    EXPECT_EQ(p1.front(), hist.front());

    auto p2 = get_part_of_history(hist, 4, 1);
    EXPECT_EQ(p2.size(), 4);
    EXPECT_EQ(p2.front(), hist[1]);

    auto p3 = get_part_of_history(hist, 5, 2);
    EXPECT_EQ(p3.size(), 5);
    EXPECT_EQ(p3.front(), hist[2]);

    EXPECT_THROW(get_part_of_history(hist, 8), std::out_of_range);
}

TEST(TestRuleUtils, Runx01x2)
{
    moveVec_t hist = {make_move("3339"), make_move("4839"), make_move("1939")};
    auto t = hist.size();
    for (size_t i = 1; i < t - 1; i++)
    {
        auto before = get_part_of_history(hist, i);
        auto left = get_part_of_history(hist, t - i, i);
        // fmt::print("before = {} size = {} left = {} size = {} total = {}\n", before, before.size(), left, left.size(), before.size() + left.size());
        EXPECT_EQ(before.size(), i);
        EXPECT_EQ(left.size(), t - i);
    }
}

TEST(TestRuleUtils, Runx01x3)
{
    moveVec_t hist = {make_move("3339"), make_move("4839"), make_move("1939"), make_move("4948"),
                      make_move("3959"), make_move("6252"), make_move("4152")};
    auto t = hist.size();
    for (size_t i = 1; i < t - 1; i++)
    {
        auto before = get_part_of_history(hist, i);
        auto left = get_part_of_history(hist, t - i, i);
        // fmt::print("before = {} size = {} left = {} size = {} total = {}\n", before, before.size(), left, left.size(), before.size() + left.size());
        EXPECT_EQ(before.size(), i);
        EXPECT_EQ(left.size(), t - i);
    }
}

// 获取给定路径的节点
std::shared_ptr<Node> get_child_node(const moveVec_t history)
{
    std::shared_ptr<Node> child;
    auto p = Node::create({});
    for (auto m : history)
    {
        try
        {
            child = p->select_child(m);
        }
        catch (const std::out_of_range &e)
        {
            child = p->gen_child(m);
            child->priority = p->child_move_set.size();
            p->children.push_back(child);
        }
        p = child;
    }
    return child;
}

TEST(TestRuleUtils, Runx02x1)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces("9/5k3/2c6/p3R4/9/9/9/8B/5C3/r2AKA3 b - - 0 1");

    b.SetPlayer(player);

    moveVec_t hist = {make_move("0030"), make_move("4030")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }

    // b.show_board();

    auto node = get_child_node(hist);

    EXPECT_EQ(get_jj_size(node), 0);
}

TEST(TestRuleUtils, Runx02x2)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_242);

    b.SetPlayer(player);

    moveVec_t hist = {make_move("0200"), make_move("4130"), make_move("0030"), make_move("4030"), make_move("6250")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }

    auto node = get_child_node(hist);

    EXPECT_EQ(get_jj_size(node), 2);
}

TEST(TestRuleUtils, Runx02x3)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_242);

    b.SetPlayer(player);

    moveVec_t hist = {make_move("0200"), make_move("4130"), make_move("2720"), make_move("3041"),
                      make_move("2050")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();

    auto node = get_child_node(hist);

    EXPECT_EQ(get_jj_size(node), 4);
}

TEST(TestRuleUtils, Runx02x4)
{
    Board b;
    b.set_pieces(rule_china_05);

    moveVec_t hist = {make_move("2928"), make_move("4847"), make_move("2848"), make_move("3748")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();

    auto node = get_child_node(hist);

    EXPECT_EQ(get_jj_size(node), 2);
}

// 序列只要一项且吃过河的兵卒，视同吃刚过河的兵卒，不算得子
TEST(TestRuleUtils, TestEatJustCrossRiverPawnx1)
{
    Board b;
    b.set_pieces("r3kab2/4a4/b8/2n1p2R1/2p6/2PpP1N2/P1C1N1p1P/B2R4c/4A4/3AK1c1r w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("4445"), make_move("4645")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(is_cross_river_pawn(hist[1].info.tgt));
    EXPECT_TRUE(is_just_cross_river_pawn(hist[1].info.tgt));
    EXPECT_TRUE(immediately_eat_just_cross_river_pawn(hist));
    EXPECT_FALSE(is_path_dezi({hist[1]}));
}

TEST(TestRuleUtils, TestEatJustCrossRiverPawnx2)
{
    Board b;
    b.set_pieces("r3kab2/4a4/b8/2n1p2R1/2p6/2PpP1N2/P1C1N1p1P/B2R4c/4A4/3AK1c1r w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("4445"), make_move("2645")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(immediately_eat_just_cross_river_pawn(hist));
}

// 不符合刚过河定义
TEST(TestRuleUtils, TestEatJustCrossRiverPawnx3)
{
    Board b;
    b.set_pieces("r3kab2/4a4/b8/2n1p2R1/2p6/2PpP1N2/P1C1N1p1P/B2R4c/4A4/3AK1c1r w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("3234"), make_move("2524")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_FALSE(immediately_eat_just_cross_river_pawn(hist));
}

TEST(TestRuleUtils, TestEatJustCrossRiverPawnx4)
{
    Board b;
    b.set_pieces("r3kab2/4a4/b8/2n1p2R1/2p6/2PpP1N2/P1C1N1p1P/B2R4c/4A4/3AK1c1r w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("3234"), make_move("2524"), make_move("3424")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(immediately_eat_just_cross_river_pawn(hist));
}

TEST(TestRuleUtils, TestEatJustCrossRiverPawnx5)
{
    Board b;
    b.set_pieces("r3kab2/4a4/b8/2n1p2R1/2p6/2PpP1N2/P1C1N1p1P/B2R4c/4A4/3AK1c1r w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("2363")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_FALSE(immediately_eat_just_cross_river_pawn(hist));
}

TEST(TestRuleUtils, TestEatJustCrossRiverPawnx6)
{
    Board b;
    b.set_pieces(rule_china_09);
    b.SetPlayer(S_BLACK);
    // b.show_board();
    moveVec_t hist = {make_move("6062"), make_move("4150"), make_move("4645")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(immediately_eat_just_cross_river_pawn({hist[2]}));
    // 吃兵前一着必须为兵过河
    EXPECT_FALSE(immediately_eat_just_cross_river_pawn(hist));
}

// 炮或马兑换车得子
TEST(TestRuleUtils, TestDezix01x1)
{
    Board b;
    b.set_pieces("1r2kabr1/2c1a4/n1c1b1n2/4p2N1/p1p6/1C4P2/P1P1P4/2N1B3C/4A4/1RBAK2R1 r - - 0 1");
    moveVec_t hist = {make_move("7668"), make_move("2868"), make_move("7079")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b1.show_board();
    // 没有升变
    auto d = path_difference(hist);
    EXPECT_FALSE(d.is_ascension());
    EXPECT_TRUE(is_path_dezi(hist));
}

// 红方无损失，净得车，得子
TEST(TestRuleUtils, TestDezix01x2)
{
    Board b;
    b.set_pieces("1r2kabr1/2c1a4/n1c1b1n2/4p2N1/p1p6/1C4P2/P1P1P4/2N1B3C/4A4/1RBAK2R1 r - - 0 1");
    moveVec_t hist = {make_move("7668"), make_move("4939"), make_move("7079")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b1.show_board();
    auto d = path_difference(hist);
    EXPECT_FALSE(d.is_ascension());
    EXPECT_TRUE(is_path_dezi(hist));
}

// 净吃过河卒
TEST(TestRuleUtils, TestDezix02x1)
{
    Board b;
    b.set_pieces("4k4/4a4/4ba3/5N3/2n3b1C/4p2p1/P4n3/4BA3/4A4/2B1K4 w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("8525"), make_move("4725"), make_move("5644")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto d = path_difference(hist);
    EXPECT_TRUE(d.is_ascension());
    // 过河兵卒等值强子价值
    auto v = get_net_gain(hist);
    EXPECT_EQ(v, STRONG_VALUE);
    EXPECT_TRUE(is_path_dezi(hist));
}

// 净吃士或象
TEST(TestRuleUtils, TestDezix02x2)
{
    Board b;
    b.set_pieces("2R2a3/4k4/3a5/9/8p/9/1p1rpn3/3CB4/4A4/2B1KA3 w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("2959")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto v = get_net_gain(hist);
    EXPECT_EQ(v, WEAK_VALUE);
    EXPECT_TRUE(is_path_dezi(hist));
}

TEST(TestRuleUtils, TestDezix02x3)
{
    Board b;
    b.set_pieces("2bak4/4a4/4b4/4CR2p/6p2/2P6/P5P1P/8c/6r2/2B1KA3 b - - 0 1");
    // 黑方无损失，红损失象
    // b.show_board();
    moveVec_t hist = {make_move("8280"), make_move("5041"), make_move("8020")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(is_path_dezi(hist));
}

// 过河兵兑吃士、象一个或多个弱子
TEST(TestRuleUtils, TestDezix02x4)
{
    Board b;
    b.set_pieces("3akab2/5P3/R8/9/9/9/9/6r1B/4A3n/3A1K3 w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("0747"), make_move("3948"), make_move("5859"), make_move("4939"), make_move("5969"), make_move("6269")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_FALSE(is_path_dezi(hist));
}

// 参考图31改编 以浮动价值的兵交换象，不算得子
TEST(TestRuleUtils, TestDezix02x5x1)
{
    Board b;
    b.set_pieces("R2ck4/4a4/4b4/4r4/2c3b1P/6N2/4C4/4B4/9/2BAKA3 b - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("2585"), make_move("4347"), make_move("6547"), make_move("6485")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto d = path_difference(hist);
    EXPECT_FALSE(d.is_ascension());
    EXPECT_FALSE(is_path_dezi(hist));
}

// 过河兵等值马或炮，不算得子
TEST(TestRuleUtils, TestDezix02x6)
{
    Board b;
    b.set_pieces("2P1kn2R/4r4/9/9/p3p4/9/4P4/4B4/9/2BAKA3 r - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("2939"), make_move("4939"), make_move("8959")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    auto d = path_difference(hist);
    EXPECT_TRUE(d.is_ascension());
    EXPECT_FALSE(is_path_dezi(hist));
}

// 兵换车得子(注意：黑方多损失一个未过河卒，无价值)
TEST(TestRuleUtils, TestDezix02x7)
{
    Board b;
    b.set_pieces("2P1kn3/5r3/9/9/p3p3R/9/4P4/4B4/9/2BAKA3 w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("8545"), make_move("5848"), make_move("2939"), make_move("4939"), make_move("4548")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(is_path_dezi(hist));
}

// 净吃象
TEST(TestRuleUtils, TestDezix02x8)
{
    Board b;
    b.set_pieces("3ak1b2/4a4/3cb3n/4p1r1p/1R3N3/P4N2P/4P4/4B4/4A4/2B1KA3 w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("5547"), make_move("6947"), make_move("5466"), make_move("8766")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(is_path_dezi(hist));
}

// 红方马换黑双象，不算得子
TEST(TestRuleUtils, TestDezix02x9x1)
{
    Board b;
    b.set_pieces("3ak1b2/4a4/3cb3n/2N1p1r1p/1R3N3/P7P/4P4/4B4/4A4/2B1KA3 w - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("5547"), make_move("6947"), make_move("2647")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_FALSE(is_path_dezi(hist));
}

// 黑方双象换双马，得子
TEST(TestRuleUtils, TestDezix02x9x2)
{
    Board b;
    b.set_pieces("3ak4/4a4/b2cb3n/4p1r1p/1RN6/P3N3P/4P4/4B4/4A4/2B1KA3 b - - 0 1");
    // b.show_board();
    moveVec_t hist = {make_move("4725"), make_move("4425"), make_move("0725"), make_move("1525")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(is_path_dezi(hist));
}

// 生成叶子节点
std::shared_ptr<Node> gen_leaf_node(const std::shared_ptr<Node> &root, const moveVec_t history)
{
    std::shared_ptr<Node> child;
    auto p = root;
    for (auto m : history)
    {
        try
        {
            child = p->select_child(m);
        }
        catch (const std::out_of_range &e)
        {
            child = p->gen_child(m);
            child->priority = p->child_move_set.size();
            p->children.push_back(child);
        }
        p = child;
    }
    return p;
}

// 参考图31 以浮动价值的兵交换象，不算得子
TEST(TestRuleUtils, Pawnx01x1)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_231);
    b.SetPlayer(player);
    JdzSimulator simulator(b, player);

    moveVec_t hist = {make_move("2585"), make_move("4547"), make_move("4647"), make_move("6485"),
                      make_move("4742"), make_move("2042")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();

    auto leaf = gen_leaf_node(simulator.root, hist);
    auto fixed = simulator.get_backward_fixed_node(leaf);
    // 过河兵换象
    EXPECT_EQ(fixed->path(), "root -> 2585 -> 4547 -> 4647 -> 6485");

    // 得子判定与净收益
    auto diff = path_difference(fixed->history);

    EXPECT_FALSE(diff.is_ascension());
    EXPECT_FALSE(diff.is_dz());

    auto v = get_net_gain(fixed->history);
    // 尽管没有得子，但将过河兵其值设定为强子价值，净收益为99
    EXPECT_EQ(v, 99);
}

TEST(TestRuleUtils, Pawnx01x2)
{
    Board b;
    auto player = S_BLACK;
    b.set_pieces(rule_china_231);
    b.SetPlayer(player);
    JdzSimulator simulator(b, player);

    // 过河兵换炮
    moveVec_t hist = {make_move("2585"), make_move("6485"), make_move("4645"), make_move("0939"),
                      make_move("4839")};
    for (auto &m : hist)
    {
        b.DoMove(m);
    }
    // b.show_board();

    auto leaf = gen_leaf_node(simulator.root, hist);
    auto fixed = simulator.get_backward_fixed_node(leaf);
    EXPECT_EQ(fixed->path(), "root -> 2585 -> 6485 -> 4645");

    // 得子判定与净收益
    auto diff = path_difference(fixed->history);

    // 升变、得子
    EXPECT_TRUE(diff.is_ascension());
    EXPECT_TRUE(diff.is_dz());

    auto v = get_net_gain(fixed->history);
    // 过河兵值设定为强子价值
    EXPECT_EQ(v, 100);
}

TEST(TestRuleUtils, CanNotOfflinex01x1)
{
    Board b;
    b.set_pieces(rule_china_239);

    moveVec_t moves = {make_move("6766"), make_move("4654"), make_move("6667")};
    for (auto &m : moves)
    {
        b.DoMove(m);
    }
    // b.show_board();
    EXPECT_TRUE(can_not_offline(b, {5, 8}));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}