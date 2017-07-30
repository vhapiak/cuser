#include <gtest/gtest.h>
#include <json.hpp>

#include "cuser/Serializer.hpp"
#include "cuser/dom/nlohmannDOM.hpp"

namespace {

template <typename T>
void check(const T& input, const nlohmann::json& expectedData)
{
    cuser::Serializer<> serializer;
    nlohmann::json data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    T output;
    serializer.read(data, output);
    EXPECT_EQ(input, output);
}

} // namespace

TEST(NlohmannTest, serializeString)
{
    const std::string input("nlohman");
    const nlohmann::json expectedData(input);
    check(input, expectedData);
}

TEST(NlohmannTest, serializeBool)
{
    const bool input(true);
    const nlohmann::json expectedData(input);
    check(input, expectedData);
}

TEST(NlohmannTest, serializeInteger)
{
    const int32_t input(42);
    const nlohmann::json expectedData(input);
    check(input, expectedData);
}

TEST(NlohmannTest, serializeFloat)
{
    const float input(42.f);
    const nlohmann::json expectedData(input);
    check(input, expectedData);
}

TEST(NlohmannTest, serializeVector)
{
    const std::vector<std::string> input{"nlohman", "json", "test"};
    const nlohmann::json expectedData(input);
    check(input, expectedData);
}

TEST(NlohmannTest, serializeObject)
{
    const std::map<int32_t, std::vector<double>> input = {
        {-1, {0.0, 0.1, 0.2}},
        {1, {0.3, 0.4, 0.5}},
    };

    const nlohmann::json expectedData{
        {"-1", {0.0, 0.1, 0.2}},
        {"1", {0.3, 0.4, 0.5}},
    };

    check(input, expectedData);
}
