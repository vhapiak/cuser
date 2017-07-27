#include <gtest/gtest.h>

#include "cuser/detail/Serializer.hpp"
#include "cuser/detail/serializers/BoolSerializer.hpp"
#include "cuser/detail/serializers/MapSerializer.hpp"

#include "dom/DOMData.hpp"
#include "dom/InDOM.hpp"
#include "dom/OutDOM.hpp"

using namespace cuser;

TEST(MapSerializerTest, serializeStringBoolMap)
{
    const std::map<std::string, bool> input = {
        {"first", true},
        {"second", false},
        {"third", true},
    };
    const test::DOMData expectedData({
        {"first", test::DOMData(true)},
        {"second", test::DOMData(false)},
        {"third", test::DOMData(true)},
    });

    detail::Serializer<detail::BoolSerializer, detail::MapSerializer>
        serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    std::map<std::string, bool> output;
    serializer.read(data, output);
    EXPECT_EQ(input, output);
}

TEST(MapSerializerTest, serializeNestedMaps)
{
    using Map = std::map<std::string, bool>;

    const std::map<std::string, Map> input = {
        {"first",
         {
             {"first_first", true},
             {"first_second", false},
             {"first_third", true},
         }},
        {"second",
         {
             {"second_first", true},
             {"second_second", false},
         }},
        {"third",
         {
             {"third_first", true},
         }},
    };

    const test::DOMData expectedData({
        {"first",
         test::DOMData{
             {"first_first", test::DOMData(true)},
             {"first_second", test::DOMData(false)},
             {"first_third", test::DOMData(true)},
         }},
        {"second",
         test::DOMData{
             {"second_first", test::DOMData(true)},
             {"second_second", test::DOMData(false)},
         }},
        {"third",
         test::DOMData{
             {"third_first", test::DOMData(true)},
         }},
    });

    detail::Serializer<detail::BoolSerializer, detail::MapSerializer>
        serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    std::map<std::string, Map> output;
    serializer.read(data, output);
    EXPECT_EQ(input, output);
}

TEST(MapSerializerTest, deserializeNull)
{
    detail::Serializer<detail::BoolSerializer, detail::MapSerializer>
        serializer;

    const test::DOMData data;
    std::map<std::string, bool> output;
    EXPECT_THROW(serializer.read(data, output), SerializerException);
}
