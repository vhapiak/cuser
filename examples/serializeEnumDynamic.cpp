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

struct FormatSerializer
{
    FormatSerializer()
        : mToString(false)
    {
    }

    void setToString(bool toString) { mToString = toString; }

    template <typename T>
    using IsSupported = std::is_same<Format, T>;

    template <typename Document, typename Serializer>
    void write(
        const Format input,
        cuser::OutDOM<Document>& output,
        Serializer& /*serializer*/)
    {
        if (mToString)
        {
            static const std::string formats[] = {"Rgb", "Yuv"};
            const std::string& str = formats[static_cast<std::size_t>(input)];
            output.setValue(str);
        }
        else
        {
            output.setValue(static_cast<uint8_t>(input));
        }
    }

private:
    bool mToString;
};

} // namespace

int main()
{
    const Format format = Format::Yuv;

    cuser::Serializer<FormatSerializer> serializer;

    {
        nlohmann::json json;
        serializer.write(format, json);
        std::cout << json << std::endl; // print 1
    }

    {
        serializer.get<FormatSerializer>().setToString(true);
        nlohmann::json json;
        serializer.write(format, json);
        std::cout << json << std::endl; // print "Yuv"
    }

    return 0;
}
