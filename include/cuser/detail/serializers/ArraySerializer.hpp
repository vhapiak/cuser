#pragma once

#include <type_traits>

#include "cuser/DOM.hpp"
#include "cuser/SerializerException.hpp"

namespace cuser {
namespace detail {

class ArraySerializer
{
public: // types
    template <typename T>
    using IsSupported = std::integral_constant<
        bool,
        std::is_array<T>::value && std::extent<T>::value != 0>;

public: // methods
    template <
        typename Document,
        typename Array,
        std::size_t N,
        typename Serializer>
    void read(
        const InDOM<Document>& input,
        Array (&output)[N],
        const Serializer& serializer) const;

    template <
        typename Array,
        std::size_t N,
        typename Document,
        typename Serializer>
    void write(
        const Array (&input)[N],
        OutDOM<Document>& output,
        Serializer& serializer);
};

template <typename Document, typename Array, std::size_t N, typename Serializer>
void ArraySerializer::read(
    const InDOM<Document>& input,
    Array (&output)[N],
    const Serializer& serializer) const
{
    if (!input.isArray())
    {
        throw SerializerException("Isn't an array");
    }
    if (input.size() != N)
    {
        throw SerializerException("Wrong numbers of elements");
    }

    for (std::size_t i = 0; i < N; ++i)
    {
        serializer.read(input[i], output[i]);
    }
}

template <typename Array, std::size_t N, typename Document, typename Serializer>
void ArraySerializer::write(
    const Array (&input)[N],
    OutDOM<Document>& output,
    Serializer& serializer)
{
    output.setArray(N);
    for (std::size_t i = 0; i < N; ++i)
    {
        auto item = output.push();
        serializer.write(input[i], item);
    }
}

} // namespace detail
} // namespace cuser
