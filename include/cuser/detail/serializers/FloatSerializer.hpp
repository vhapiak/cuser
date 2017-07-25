#pragma once

#include <type_traits>

#include "cuser/DOM.hpp"
#include "cuser/SerializerException.hpp"

namespace cuser {
namespace detail {

class FloatSerializer
{
public: // types
    template <typename T>
    using IsSupported = std::is_floating_point<T>;

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
void FloatSerializer::read(
    const InDOM<Document>& input,
    Data& output,
    const Serializer& /*serializer*/) const
{
    if (input.isInteger())
    {
        int64_t i;
        input.getValue(i);
        output = static_cast<Data>(i);
        return;
    }

    if (input.isFloat())
    {
        input.getValue(output);
        return;
    }

    throw SerializerException("Isn't a number");
}

template <typename Data, typename Document, typename Serializer>
void FloatSerializer::write(
    const Data& input,
    OutDOM<Document>& output,
    Serializer& /*serializer*/)
{
    output.setValue(input);
}

} // namespace detail
} // namespace cuser
