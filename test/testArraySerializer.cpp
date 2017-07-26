#include <gtest/gtest.h>

#include "cuser/detail/Serializer.hpp"
#include "cuser/detail/serializers/ArraySerializer.hpp"
#include "cuser/detail/serializers/BoolSerializer.hpp"

#include "dom/DOMData.hpp"
#include "dom/InDOM.hpp"
#include "dom/OutDOM.hpp"

using namespace cuser;

TEST(ArraySerializerTest, serializeBoolArray)
{
    const bool input[] = {true, false, true};
    const test::DOMData expectedData(
        {test::DOMData(true), test::DOMData(false), test::DOMData(true)});

    detail::Serializer<detail::BoolSerializer, detail::ArraySerializer>
        serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    bool output[3];
    serializer.read(data, output);
    EXPECT_EQ(input[0], output[0]);
    EXPECT_EQ(input[1], output[1]);
    EXPECT_EQ(input[2], output[2]);
}

TEST(ArraySerializerTest, deserializeNull)
{
    const test::DOMData input;

    detail::Serializer<detail::BoolSerializer, detail::ArraySerializer>
        serializer;

    bool output[3];
    EXPECT_THROW(serializer.read(input, output), SerializerException);
}

TEST(ArraySerializerTest, deserializeGeterogenArray)
{
    const test::DOMData input({test::DOMData(true), test::DOMData(1.f)});

    detail::Serializer<detail::BoolSerializer, detail::ArraySerializer>
        serializer;

    bool output[2];
    EXPECT_THROW(serializer.read(input, output), SerializerException);
}

TEST(ArraySerializerTest, deserializeWrongSizeArray)
{
    const test::DOMData input({test::DOMData(true)});

    detail::Serializer<detail::BoolSerializer, detail::ArraySerializer>
        serializer;

    bool output[2];
    EXPECT_THROW(serializer.read(input, output), SerializerException);
}
