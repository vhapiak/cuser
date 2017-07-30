#include <gtest/gtest.h>

#include "cuser/detail/Serializer.hpp"
#include "cuser/detail/serializers/IOStreamSerializer.hpp"

#include "dom/DOMData.hpp"
#include "dom/InDOM.hpp"
#include "dom/OutDOM.hpp"

using namespace cuser;

namespace {

struct Color
{
    uint16_t r, g, b, a;
};

std::istream& operator>>(std::istream& in, Color& color)
{
    char coma;
    in >> color.r >> coma;
    if (coma != ',')
    {
        in.setstate(std::istream::failbit);
    }
    in >> color.g >> coma;
    if (coma != ',')
    {
        in.setstate(std::istream::failbit);
    }
    in >> color.b >> coma;
    if (coma != ',')
    {
        in.setstate(std::istream::failbit);
    }
    in >> color.a;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Color& color)
{
    out << color.r << ',' << color.g << ',' << color.b << ',' << color.a;
    return out;
}

bool operator==(const Color& l, const Color& r)
{
    return l.r == r.r && l.g == r.g && l.b == r.b && l.a == r.a;
}

struct Fail
{
};

std::ostream& operator<<(std::ostream& out, const Fail&)
{
    out.setstate(std::ostream::failbit);
    return out;
}

} // namespace

TEST(IOStreamSerializerTest, serializeObject)
{
    const Color input = {1, 2, 3, 4};
    const test::DOMData expectedData(std::string("1,2,3,4"));

    detail::Serializer<detail::IOStreamSerializer> serializer;

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    Color output;
    serializer.read(data, output);
    EXPECT_EQ(input, output);
}

TEST(IOStreamSerializerTest, deserializeNull)
{
    detail::Serializer<detail::IOStreamSerializer> serializer;
    test::DOMData data;
    int output;
    EXPECT_THROW(serializer.read(data, output), cuser::SerializerException);
}

TEST(IOStreamSerializerTest, deserializeTrash)
{
    detail::Serializer<detail::IOStreamSerializer> serializer;
    test::DOMData data(std::string("ffaabbcc"));
    Color output;
    EXPECT_THROW(serializer.read(data, output), cuser::SerializerException);
}

TEST(IOStreamSerializerTest, serializeWithError)
{
    detail::Serializer<detail::IOStreamSerializer> serializer;
    const Fail input;
    test::DOMData data;
    EXPECT_THROW(serializer.write(input, data), cuser::SerializerException);
}
