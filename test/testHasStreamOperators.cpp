#include <gtest/gtest.h>

#include "cuser/utils/HasStreamOperators.hpp"

namespace {

struct Without
{
};

struct Within
{
};

std::istream& operator>>(std::istream& in, Within&)
{
    return in;
}

std::ostream& operator<<(std::ostream& out, const Within&)
{
    return out;
}

} // namespace

TEST(HasStreamOpertorsTest, istream)
{
    EXPECT_EQ(true, cuser::HasIstreamOperator<double>::value);
    EXPECT_EQ(false, cuser::HasIstreamOperator<Without>::value);
    EXPECT_EQ(true, cuser::HasIstreamOperator<Within>::value);
}

TEST(HasStreamOpertorsTest, ostream)
{
    EXPECT_EQ(true, cuser::HasOstreamOperator<double>::value);
    EXPECT_EQ(false, cuser::HasOstreamOperator<Without>::value);
    EXPECT_EQ(true, cuser::HasOstreamOperator<Within>::value);
}
