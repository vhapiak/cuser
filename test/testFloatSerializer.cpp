#include <gtest/gtest.h>

#include "cuser/detail/Serializer.hpp"
#include "cuser/detail/serializers/FloatSerializer.hpp"

#include "dom/DOMData.hpp"
#include "dom/InDOM.hpp"
#include "dom/OutDOM.hpp"

using namespace cuser;

TEST(FloatSerializerTest, serializeFloat)
{
    const float input = 2.4f;
    const test::DOMData expectedData(input);

    detail::Serializer<detail::FloatSerializer> serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    float output;
    serializer.read(data, output);
    EXPECT_FLOAT_EQ(input, output);
}

TEST(FloatSerializerTest, deserializeInteger)
{
    const float expectedOutput = 2.0f;
    const test::DOMData input(2);

    detail::Serializer<detail::FloatSerializer> serializer;

    float output;
    serializer.read(input, output);
    EXPECT_FLOAT_EQ(expectedOutput, output);
}

TEST(FloatSerializerTest, deserializeNull)
{
    const test::DOMData input;

    detail::Serializer<detail::FloatSerializer> serializer;

    float output;
    EXPECT_THROW(serializer.read(input, output), SerializerException);
}
