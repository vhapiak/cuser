#pragma once

#include <sstream>

#include "cuser/DOM.hpp"
#include "cuser/SerializerException.hpp"
#include "cuser/utils/HasStreamOperators.hpp"

namespace cuser {
namespace detail {

class IOStreamSerializer
{
public: // types
    template <typename T>
    using IsSupported = std::integral_constant<
        bool,
        HasIstreamOperator<T>::value || HasOstreamOperator<T>::value>;

public: // methods
    template <typename Document, typename Data, typename Serializer>
    void read(
        const InDOM<Document>& input,
        Data& output,
        const Serializer& serializer) const;

    template <typename Data, typename Document, typename Serializer>
    void write(
        const Data& input,
        OutDOM<Document>& output,
        Serializer& serializer);
};

template <typename Document, typename Data, typename Serializer>
void IOStreamSerializer::read(
    const InDOM<Document>& input,
    Data& output,
    const Serializer& /*serializer*/) const
{
    if (!input.isString())
    {
        throw SerializerException("Isn't a string");
    }
    std::string str;
    input.getValue(str);
    std::stringstream ss(str);
    ss >> output;
    if (ss.fail())
    {
        throw SerializerException("Cannot read value from stream");
    }
}

template <typename Data, typename Document, typename Serializer>
void IOStreamSerializer::write(
    const Data& input,
    OutDOM<Document>& output,
    Serializer& /*serializer*/)
{
    std::stringstream ss;
    ss << input;
    if (ss.fail())
    {
        throw SerializerException("Cannot write value to stream");
    }
    output.setValue(ss.str());
}

} // namespace detail
} // namespace cuser
