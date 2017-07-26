#include <gtest/gtest.h>

#include "cuser/detail/Serializer.hpp"
#include "cuser/detail/serializers/BoolSerializer.hpp"

#include "dom/DOMData.hpp"
#include "dom/InDOM.hpp"
#include "dom/OutDOM.hpp"

using namespace cuser;

TEST(BoolSerializerTest, serializeBool)
{
    const bool input = true;
    const test::DOMData expectedData(input);

    detail::Serializer<detail::BoolSerializer> serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    bool output;
    serializer.read(data, output);
    EXPECT_EQ(input, output);
}

TEST(BoolSerializerTest, deserializeInteger)
{
    const test::DOMData input(1);

    detail::Serializer<detail::BoolSerializer> serializer;

    bool output;
    EXPECT_THROW(serializer.read(input, output), SerializerException);
}

TEST(BoolSerializerTest, deserializeNull)
{
    const test::DOMData input;

    detail::Serializer<detail::BoolSerializer> serializer;

    bool output;
    EXPECT_THROW(serializer.read(input, output), SerializerException);
}
