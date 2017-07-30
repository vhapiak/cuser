#include <gtest/gtest.h>
#include <type_traits>

#include "cuser/Serializer.hpp"

#include "dom/DOMData.hpp"
#include "dom/InDOM.hpp"
#include "dom/OutDOM.hpp"

namespace {

enum class Format : uint32_t
{
    Rgba,
    Rgb,
};

struct FormatSerializer
{
    FormatSerializer(bool toText);

    template <typename T>
    using IsSupported = std::is_same<Format, T>;

    template <typename Document, typename Serializer>
    void read(
        const cuser::InDOM<Document>& input,
        Format& output,
        const Serializer& serializer) const;

    template <typename Document, typename Serializer>
    void write(
        Format input,
        cuser::OutDOM<Document>& output,
        const Serializer& serializer) const;

private: //
    bool mToText;
};

FormatSerializer::FormatSerializer(bool toText)
    : mToText(toText)
{
}

template <typename Document, typename Serializer>
void FormatSerializer::read(
    const cuser::InDOM<Document>& input,
    Format& output,
    const Serializer& /*serializer*/) const
{
    if (mToText)
    {
        if (!input.isString())
        {
            throw cuser::SerializerException("Isn't a string");
        }

        static const std::map<std::string, Format> formats = {
            {"Rgba", Format::Rgba},
            {"Rgb", Format::Rgb},
        };

        std::string value;
        input.getValue(value);

        output = formats.at(value);
    }
    else
    {
        if (!input.isInteger())
        {
            throw cuser::SerializerException("Isn't an integer");
        }

        uint32_t value;
        input.getValue(value);
        output = static_cast<Format>(value);
    }
}

template <typename Document, typename Serializer>
void FormatSerializer::write(
    Format input,
    cuser::OutDOM<Document>& output,
    const Serializer& /*serializer*/) const
{
    if (mToText)
    {
        static const std::string formats[] = {"Rgba", "Rgb"};
        output.setValue(formats[static_cast<std::size_t>(input)]);
    }
    else
    {
        output.setValue(static_cast<uint32_t>(input));
    }
}

} // namespace

using namespace cuser;

TEST(CustomSerializerTest, serializeFormatToText)
{
    const Format input = Format::Rgb;
    const test::DOMData expectedData(std::string("Rgb"));

    auto serializer = makeSerializer(FormatSerializer{true});

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    Format output;
    serializer.read(data, output);
    EXPECT_EQ(input, output);
}

TEST(CustomSerializerTest, serializeFormatToInt)
{
    const Format input = Format::Rgb;
    const test::DOMData expectedData(1u);

    auto serializer = makeSerializer(FormatSerializer{false});

    test::DOMData data;
    serializer.write(input, data);
    EXPECT_EQ(expectedData, data);

    Format output;
    serializer.read(data, output);
    EXPECT_EQ(input, output);
}
