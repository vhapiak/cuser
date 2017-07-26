#pragma once

#include <type_traits>

#include "cuser/DOM.hpp"
#include "cuser/SerializerException.hpp"

namespace cuser {
namespace detail {

class BoolSerializer
{
public: // types
    template <typename T>
    using IsSupported = std::is_same<bool, T>;

public: // methods
    template <typename Document, typename Serializer>
    void read(
        const InDOM<Document>& input,
        bool& output,
        const Serializer& serializer) const;

    template <typename Document, typename Serializer>
    void write(
        const bool& input,
        OutDOM<Document>& output,
        Serializer& serializer);
};

template <typename Document, typename Serializer>
void BoolSerializer::read(
    const InDOM<Document>& input,
    bool& output,
    const Serializer& /*serializer*/) const
{
    if (!input.isBool())
    {
        throw SerializerException("Isn't a boolean");
    }
    input.getValue(output);
}

template <typename Document, typename Serializer>
void BoolSerializer::write(
    const bool& input,
    OutDOM<Document>& output,
    Serializer& /*serializer*/)
{
    output.setValue(input);
}

} // namespace detail
} // namespace cuser
