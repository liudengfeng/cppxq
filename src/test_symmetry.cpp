/**
 * Copyright (c) 2018-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**
 * Acknowledgement:
 * These tests are loosely ported from the MiniGo project's excellent unit
 * tests. https://github.com/tensorflow/minigo
 */
#include <gtest/gtest.h>
#include <array>
#include <vector>

#include "xq_state.hpp"
#include "board_feature.hpp"
// #include "test_utils.h"

static constexpr size_t kBoardRegion = BOARD_HEIGHT * BOARD_WIDTH;

float *boardPlane(float *features, int idx)
{
    return features + idx * BOARD_HEIGHT * BOARD_WIDTH;
}

const float *boardPlane(const float *features, int idx)
{
    return features + idx * BOARD_HEIGHT * BOARD_WIDTH;
}

bool featEqual(const float *feat1, const float *feat2, size_t N)
{
    // assert(feat1.size() == feat2.size());
    for (size_t i = 0; i < N; ++i)
    {
        if (fabs(feat1[i] - feat2[i]) > 1e-3)
        {
            return false;
        }
    }
    return true;
}

void InvTransform(const BoardFeature &bf, const float *feat, float *featBack)
{
    // for plane i
    // 中国象棋 252 + 3
    for (int i = 0; i < 255; ++i)
    {
        const float *planeFeat = boardPlane(feat, i);
        float *planeFeatBack = boardPlane(featBack, i);
        // inv-transform
        for (int x = 0; x < BOARD_WIDTH; ++x)
        {
            for (int y = 0; y < BOARD_HEIGHT; ++y)
            {
                // get xy as a std::pair<int, int>
                auto xy = bf.InvTransform(std::make_pair(x, y));
                // int offset = EXPORT_OFFSET_XY(x, y);
                // int offsetBack = EXPORT_OFFSET_XY(xy.first, xy.second);
                Coord origin = Coord(xy.first, xy.second);
                Coord back = origin.fliplr();
                // 最后三项为常数，坐标互换没有影响
                planeFeatBack[back.id()] = planeFeat[origin.id()];
            }
        }
    }
}

// in case we want to print the feature for further debug
void printFeat(float *data)
{
    for (int i = 0; i < 3; ++i)
    {
        float *planeData = boardPlane(data, i);
        std::cout << "plane " << i << ": " << std::endl;
        for (size_t j = 0; j < kBoardRegion; ++j)
        {
            std::cout << planeData[j] << " ";
            if ((j + 1) % BOARD_WIDTH == 0)
            {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

TEST(SymmetryTest, testCodex1)
{
    XqState s;
    BoardFeature bf(s);
    for (int i = 0; i < 18; ++i)
    {
        bf.setD4Code(i);
        if (i % 2 == 0)
        {
            EXPECT_EQ(bf.getD4Code(), 0);
        }
        else
        {
            EXPECT_EQ(bf.getD4Code(), 1);
        }
    }
}

TEST(SymmetryTest, testCodex2)
{
    std::mt19937 rng;
    XqState s;
    BoardFeature randomBf = BoardFeature::RandomShuffle(s, &rng);
    for (int i = 0; i < 18; ++i)
    {
        randomBf.setD4Code(i);
        if (i % 2 == 0)
        {
            EXPECT_EQ(randomBf.getD4Code(), 0);
        }
        else
        {
            EXPECT_EQ(randomBf.getD4Code(), 1);
        }
    }
}

TEST(SymmetryTest, testInversions)
{
    std::mt19937 rng;
    XqState s;
    Move m;
    // play some random moves
    m = make_move("7242");
    s.forward(m);
    m = make_move("7967");
    s.forward(m);

    BoardFeature bf(s);
    BoardFeature randomBf = BoardFeature::RandomShuffle(s, &rng);

    std::array<float, kBoardRegion * 255> agzFeat;
    std::array<float, kBoardRegion * 255> agzFeatSymm;
    std::array<float, kBoardRegion * 255> agzFeatBack;

    auto player1 = bf.state().nextPlayer();
    auto player2 = randomBf.state().nextPlayer();
    EXPECT_EQ(player1, player2);

    // 只有二种方式
    // directly extract
    bf.extractAGZ(agzFeat.data());

    // extract feature with symmetry_type = i
    randomBf.setD4Code(1);
    randomBf.extractAGZ(agzFeatSymm.data());
    // apply the symmetry back
    InvTransform(randomBf, agzFeatSymm.data(), agzFeatBack.data());

    // check still equal after transformed back
    // 最后三个plane不变
    for (size_t j = 0; j < kBoardRegion * 255; ++j)
    {
        EXPECT_FLOAT_EQ(agzFeat[j], agzFeatBack[j]);
    }
    // }
}

// We didn't extract the feature first and then
// apply symmetry on it (different from minigo)
// so we test on the move
TEST(SymmetryTest, testCompositions)
{
    std::mt19937 rng1;
    std::mt19937 rng2;
    std::mt19937 rng3;
    XqState s;

    BoardFeature randomBf1 = BoardFeature::RandomShuffle(s, &rng1);
    BoardFeature randomBf2 = BoardFeature::RandomShuffle(s, &rng2);
    // BoardFeature randomBf3 = BoardFeature::RandomShuffle(s, &rng3);

    randomBf1.setD4Group(BoardFeature::CCW180, false);

    for (int x = 0; x < BOARD_WIDTH; ++x)
    {
        for (int y = 0; y < BOARD_HEIGHT; ++y)
        {
            Coord c1(x, y);
            auto pair1 = randomBf1.Transform(std::make_pair(x, y));
            EXPECT_EQ(pair1.first, c1.fliplr().x);
            EXPECT_EQ(pair1.second, c1.fliplr().y);
        }
    }

    randomBf1.setD4Group(BoardFeature::NONE, false);
    randomBf2.setD4Group(BoardFeature::CCW180, false);
    for (int x = 0; x < BOARD_WIDTH; ++x)
    {
        for (int y = 0; y < BOARD_HEIGHT; ++y)
        {
            Coord c1(x, y);
            auto pair1 = randomBf1.Transform(std::make_pair(x, y));
            auto pair2 = randomBf2.Transform(pair1);

            EXPECT_EQ(pair1.first, c1.x);
            EXPECT_EQ(pair1.second, c1.y);

            EXPECT_EQ(pair2.first, c1.fliplr().x);
            EXPECT_EQ(pair2.second, c1.fliplr().y);
        }
    }
}

// Test different symmetries generates
// different results on both feature and probability
TEST(SymmetryTest, testUniqueness)
{
    std::mt19937 rng1;
    std::mt19937 rng2;
    XqState s;
    Move m;
    // play some random moves
    m = make_move("7242");
    s.forward(m);
    m = make_move("7967");
    s.forward(m);

    BoardFeature randomBf1 = BoardFeature::RandomShuffle(s, &rng1);
    BoardFeature randomBf2 = BoardFeature::RandomShuffle(s, &rng2);

    std::array<float, kBoardRegion * 255> agzFeat1;
    std::array<float, kBoardRegion * 255> agzFeat2;

    for (int i = 0; i < 2; ++i)
    {
        randomBf1.setD4Code(i);
        randomBf1.extractAGZ(agzFeat1.data());

        for (int j = i + 1; j < 2; ++j)
        {
            randomBf2.setD4Code(j);
            randomBf2.extractAGZ(agzFeat2.data());

            // expect agz1 and agz2 not equal
            EXPECT_FALSE(
                featEqual(agzFeat1.data(), agzFeat2.data(), kBoardRegion * 255));
        }
    }

    /* simulate applying random symmetry on output pi:
      std::default_random_engine generator;
      std::uniform_real_distribution<double> distribution(0.0,1.0);
      std::vector<float> pi(0., kBoardRegion + 1);
      for (size_t i = 0; i < pi.size(); ++i)
        pi[i] = distribution(generator);
      std::unordered_map<int, float> output_pi1;
      std::unordered_map<int, float> output_pi2;
    */
    for (int i = 0; i < 2; ++i)
    {
        randomBf1.setD4Code(i);
        for (int j = i + 1; j < 2; ++j)
        {
            randomBf2.setD4Code(j);

            // check at least one coord not equal
            bool flag = true;
            for (size_t k = 0; k < kBoardRegion + 1; ++k)
            {
                Move m1 = randomBf1.action2Move(k);
                Move m2 = randomBf2.action2Move(k);
                if (m1 != m2)
                {
                    flag = false;
                    break;
                }
            }
            EXPECT_FALSE(flag);
        }
    }
}

// Check that the reinterpretation of
// kBoardRegion = BOARD_HEIGHT * BOARD_WIDTH + 1 during symmetry
// application is consistent with coords.from_flat
TEST(SymmetryTest, testProperMoveTransform)
{
    std::mt19937 rng;
    XqState s;

    BoardFeature randomBf = BoardFeature::RandomShuffle(s, &rng);

    for (int i = 0; i < 2; ++i)
    {
        // 最终由代码决定是否棋子左右互换
        randomBf.setD4Code(i);
        for (size_t j = 0; j < BOARD_NUM_ACTION; ++j)
        {
            Move invt_move = randomBf.action2Move(j);
            // 0: 0001; 1: 0002; 2: 0003
            // 原始映射构造
            Move move = make_move(I2M.at(j));
            if (i % 2 == 1)
            {
                move = move.fliplr();
            }
            EXPECT_EQ(move.toString(), invt_move.toString());
        }
    }
    // 默认构造 9090
    Move m;
    EXPECT_EQ(randomBf.action2Move(-1).toString(), m.toString());
    EXPECT_FALSE(m.IsValid());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}