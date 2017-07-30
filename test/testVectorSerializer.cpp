#include <gtest/gtest.h>

#include "cuser/detail/Serializer.hpp"
#include "cuser/detail/serializers/BoolSerializer.hpp"
#include "cuser/detail/serializers/VectorSerializer.hpp"

#include "dom/DOMData.hpp"
#include "dom/InDOM.hpp"
#include "dom/OutDOM.hpp"

using namespace cuser;

TEST(VectorSerializerTest, isVector)
{
    std::vector<bool> simple;
    std::vector<std::vector<bool>> nested;
    EXPECT_EQ(true, detail::IsVector<decltype(simple)>::value);
    EXPECT_EQ(true, detail::IsVector<decltype(nested)>::value);
}

TEST(VectorSerializerTest, serializeBoolVector)
{
    const std::vector<bool> input = {true, false, true};
    const test::DOMData expectedData(
        {test::DOMData(true), test::DOMData(false), test::DOMData(true)});

    detail::Serializer<detail::BoolSerializer, detail::VectorSerializer>
        serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    std::vector<bool> output;
    serializer.read(data, output);
    EXPECT_EQ(input.size(), output.size());
    for (std::size_t i = 0; i < output.size(); ++i)
    {
        EXPECT_EQ(input[i], output[i]);
    }
}

TEST(VectorSerializerTest, serializeNestedVectors)
{
    const std::vector<std::vector<bool>> input = {
        {true, false, true},
        {false, true},
        {true},
    };
    const test::DOMData expectedData({
        test::DOMData{
            test::DOMData(true), test::DOMData(false), test::DOMData(true)},
        test::DOMData{test::DOMData(false), test::DOMData(true)},
        test::DOMData{test::DOMData(true)},
    });

    detail::Serializer<detail::BoolSerializer, detail::VectorSerializer>
        serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    std::vector<std::vector<bool>> output;
    serializer.read(data, output);
    EXPECT_EQ(input.size(), output.size());
    for (std::size_t i = 0; i < input.size(); ++i)
    {
        EXPECT_EQ(input[i].size(), output[i].size());
        for (std::size_t j = 0; j < input[i].size(); ++j)
        {
            EXPECT_EQ(input[i][j], output[i][j]);
        }
    }
}

TEST(VectorSerializerTest, deserializeNull)
{
    const test::DOMData input;

    detail::Serializer<detail::BoolSerializer, detail::VectorSerializer>
        serializer;

    std::vector<bool> output;
    EXPECT_THROW(serializer.read(input, output), SerializerException);
}
