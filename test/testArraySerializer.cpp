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
    for (std::size_t i = 0; i < std::extent<decltype(output)>::value; ++i)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(ArraySerializerTest, serializeMultiArray)
{
    const bool input[3][3] = {
        {true, false, true},
        {false, true, false},
        {true, true, true},
    };
    const test::DOMData expectedData({
        test::DOMData{
            test::DOMData(true), test::DOMData(false), test::DOMData(true)},
        test::DOMData{
            test::DOMData(false), test::DOMData(true), test::DOMData(false)},
        test::DOMData{
            test::DOMData(true), test::DOMData(true), test::DOMData(true)},
    });

    detail::Serializer<detail::BoolSerializer, detail::ArraySerializer>
        serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    bool output[3][3];
    serializer.read(data, output);
    for (std::size_t i = 0; i < std::extent<decltype(output)>::value; ++i)
    {
        for (std::size_t j = 0; j < std::extent<decltype(output), 1>::value;
             ++j)
        {
            EXPECT_EQ(input[i][j], output[i][j]);
        }
    }
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
