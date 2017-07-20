#include <gtest/gtest.h>

#include "cuser/utils/LastIndexOf.hpp"

TEST(LastIndexOfTest, noMatches)
{
    EXPECT_EQ(1, (cuser::LastIndexOf<bool, true, false>::value));
    EXPECT_EQ(2, (cuser::LastIndexOf<bool, true, false, false>::value));
}

TEST(LastIndexOfTest, singleMatches)
{
    EXPECT_EQ(1, (cuser::LastIndexOf<bool, true, false, true>::value));
    EXPECT_EQ(0, (cuser::LastIndexOf<bool, true, true, false>::value));
    EXPECT_EQ(1, (cuser::LastIndexOf<bool, true, false, true, false>::value));
}

TEST(LastIndexOfTest, multipleMatches)
{
    EXPECT_EQ(2, (cuser::LastIndexOf<bool, true, false, true, true>::value));
    EXPECT_EQ(2, (cuser::LastIndexOf<bool, true, true, false, true>::value));
    EXPECT_EQ(1, (cuser::LastIndexOf<bool, true, true, true, false>::value));
}
