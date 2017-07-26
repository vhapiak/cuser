#pragma once

#include <type_traits>

#include "cuser/DOM.hpp"
#include "cuser/SerializerException.hpp"

namespace cuser {
namespace detail {

class IntegerSerializer
{
public: // types
    template <typename T>
    using IsSupported = std::integral_constant<
        bool,
        std::is_integral<T>::value || !std::is_same<bool, T>::value>;

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
void IntegerSerializer::read(
    const InDOM<Document>& input,
    Data& output,
    const Serializer& /*serializer*/) const
{
    if (!input.isInteger())
    {
        throw SerializerException("Isn't an integer");
    }
    input.getValue(output);
}

template <typename Data, typename Document, typename Serializer>
void IntegerSerializer::write(
    const Data& input,
    OutDOM<Document>& output,
    Serializer& /*serializer*/)
{
    output.setValue(input);
}

} // namespace detail
} // namespace cuser
