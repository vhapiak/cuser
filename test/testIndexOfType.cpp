#include <gtest/gtest.h>

#include "cuser/utils/IndexOfType.hpp"

TEST(IndexOfTypeTest, noMatches)
{
    EXPECT_EQ(1, (cuser::IndexOfType<bool, double>::value));
    EXPECT_EQ(3, (cuser::IndexOfType<bool, double, int, float>::value));
}

TEST(IndexOfTypeTest, matches)
{
    EXPECT_EQ(0, (cuser::IndexOfType<bool, bool>::value));
    EXPECT_EQ(1, (cuser::IndexOfType<double, int, double, float>::value));
    EXPECT_EQ(2, (cuser::IndexOfType<float, int, double, float>::value));
}
