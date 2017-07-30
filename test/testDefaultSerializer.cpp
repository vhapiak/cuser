#include <gtest/gtest.h>

#include "cuser/Serializer.hpp"

#include "dom/DOMData.hpp"
#include "dom/InDOM.hpp"
#include "dom/OutDOM.hpp"

using namespace cuser;

TEST(DefaultSerializerTest, serializeComplexData)
{
    using Data = std::map<int32_t, std::vector<double>>;

    const Data input = {
        {-1, {0.0, 0.1, 0.2}},
        {1, {0.3, 0.4, 0.5}},
    };

    const test::DOMData expectedData{
        {"-1",
         test::DOMData{
             test::DOMData{0.0}, test::DOMData{0.1}, test::DOMData{0.2}}},
        {"1",
         test::DOMData{
             test::DOMData{0.3}, test::DOMData{0.4}, test::DOMData{0.5}}},
    };

    Serializer<> serializer;
    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    Data output;
    serializer.read(data, output);
    EXPECT_EQ(input, output);
}
