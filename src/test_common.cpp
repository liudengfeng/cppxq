#include <gtest/gtest.h>
#include <set>

#include "hash_num.hpp"
#include "common.hpp"

// 测试唯一
TEST(TestCommon, HashNum)
{
    std::set<uint64_t> hashs;
    for (size_t i = 0; i < 7 * 2 * NUM_INTERSECTION; i++)
    {
        hashs.insert(_board_hash[i]);
    }
    EXPECT_EQ(static_cast<int>(hashs.size()), 7 * 2 * NUM_INTERSECTION);
}


TEST(TestCommon, MoveIsValid)
{
    Move m;
    EXPECT_EQ(m.toString(), "9999");
    EXPECT_FALSE(m.IsValid());

    Move m1(2, 0, 3, 8);
    EXPECT_EQ(m1.toString(), "2038");
    EXPECT_TRUE(m1.IsValid());
}

TEST(TestCommon, CoordCmp)
{
    const Coord c1(0, 0);
    const Coord c2(2, 6);
    const Coord c3(3, 3);
    const Coord c4(4, 6);
    const Coord c5(4, 6);
    EXPECT_LT(c1, c2);
    EXPECT_GT(c2, c3);
    EXPECT_EQ(c2.id(), c2.y * BOARD_WIDTH + c2.x);
    EXPECT_EQ(c3.id(), c3.y * BOARD_WIDTH + c3.x);
    EXPECT_EQ(c4, c5);
}

TEST(TestCommon, MoveCmp)
{
    Move m1(0, 0, 0, 1);
    Move m2(0, 0, 0, 2);
    Move m3(8, 3, 0, 1);
    Move m4(8, 3, 0, 2);
    Move m5(8, 3, 0, 2);
    EXPECT_LT(m1, m2);
    EXPECT_GT(m3, m2);
    EXPECT_EQ(m4, m5);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}