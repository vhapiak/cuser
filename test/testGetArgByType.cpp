#include <gtest/gtest.h>

#include "cuser/utils/GetArgByType.hpp"

TEST(GetArgByTypeTest, noMatches)
{
    EXPECT_EQ(false, cuser::GetArgByType<bool>::get(1.0, 1.f, 1u));
    EXPECT_EQ(0.0, cuser::GetArgByType<double>::get(true, 1.f, 1u));
}

TEST(GetArgByTypeTest, getArgs)
{
    EXPECT_EQ(true, cuser::GetArgByType<bool>::get(1.0, true, 1.f, 1u));
    EXPECT_EQ(1.0, cuser::GetArgByType<double>::get(1.0, true, 1.f, 1u));
    EXPECT_EQ(1.f, cuser::GetArgByType<float>::get(1.0, true, 1.f, 1u));
    EXPECT_EQ(1u, cuser::GetArgByType<uint32_t>::get(1.0, true, 1.f, 1u));
}
