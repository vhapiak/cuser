#include <cuser/Serializer.hpp>
#include <cuser/dom/nlohmann/OutDOM.hpp>
#include <iostream>
#include <json.hpp>

namespace {

enum class Format : uint8_t
{
    Rgb,
    Yuv
};

struct FormatToStrSerializer
{
    template <typename T>
    using IsSupported = std::is_same<Format, T>;

    template <typename Document, typename Serializer>
    void write(
        const Format input,
        cuser::OutDOM<Document>& output,
        Serializer& /*serializer*/)
    {
        static const std::string formats[] = {"Rgb", "Yuv"};
        const std::string& str = formats[static_cast<std::size_t>(input)];
        output.setValue(str);
    }
};

struct FormatToIntSerializer
{
    template <typename T>
    using IsSupported = std::is_same<Format, T>;

    template <typename Document, typename Serializer>
    void write(
        const Format input,
        cuser::OutDOM<Document>& output,
        Serializer& /*serializer*/)
    {
        output.setValue(static_cast<uint8_t>(input));
    }
};

} // namespace

int main()
{
    const Format format = Format::Yuv;

    {
        auto serializer = cuser::makeSerializer(FormatToStrSerializer{});
        nlohmann::json json;
        serializer.write(format, json);
        std::cout << json << std::endl; // print "Yuv"
    }

    {
        auto serializer = cuser::makeSerializer(FormatToIntSerializer{});
        nlohmann::json json;
        serializer.write(format, json);
        std::cout << json << std::endl; // print 1
    }

    return 0;
}
