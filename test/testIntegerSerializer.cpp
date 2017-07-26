#include <gtest/gtest.h>

#include "cuser/detail/Serializer.hpp"
#include "cuser/detail/serializers/IntegerSerializer.hpp"

#include "dom/DOMData.hpp"
#include "dom/InDOM.hpp"
#include "dom/OutDOM.hpp"

using namespace cuser;

TEST(IntegerSerializerTest, serializeBool)
{
    const uint32_t input = 15;
    const test::DOMData expectedData(input);

    detail::Serializer<detail::IntegerSerializer> serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    uint32_t output;
    serializer.read(data, output);
    EXPECT_EQ(input, output);
}

TEST(IntegerSerializerTest, deserializeFloat)
{
    const test::DOMData input(1.0);

    detail::Serializer<detail::IntegerSerializer> serializer;

    uint32_t output;
    EXPECT_THROW(serializer.read(input, output), SerializerException);
}

TEST(IntegerSerializerTest, deserializeNull)
{
    const test::DOMData input;

    detail::Serializer<detail::IntegerSerializer> serializer;

    int32_t output;
    EXPECT_THROW(serializer.read(input, output), SerializerException);
}
