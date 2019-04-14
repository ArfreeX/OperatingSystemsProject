#include "../src/helpers/Randomizer.cpp"
#include "../src/assets/Ball.h"
#include <gtest/gtest.h>


TEST(DrawSpeedTest, PositiveSpeed)
{
    auto numberOfRepeats = 200000u;

    for(auto i = 0u; i < numberOfRepeats; i++)
    {
        EXPECT_GT(helpers::Randomizer::drawSpeed(), 0);
    }
}


TEST(DrawDirectionTest, DirectionIsValid)
{
    auto numberOfRepeats = 200000u;

    for(auto i = 0u; i < numberOfRepeats; i++)
    {
        auto testDirection = helpers::Randomizer::drawDirection();
        EXPECT_TRUE(testDirection == Direction::LEFT or
                    testDirection == Direction::RIGHT or
                    testDirection == Direction::TOP or
                    testDirection == Direction::BOTTOM or
                    testDirection == Direction::TOP_LEFT or
                    testDirection == Direction::TOP_RIGHT or
                    testDirection == Direction::BOTTOM_LEFT or
                    testDirection == Direction::BOTTOM_RIGHT);
    }
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
