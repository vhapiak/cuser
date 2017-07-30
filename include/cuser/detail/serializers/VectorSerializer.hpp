#pragma once

#include <vector>

#include <type_traits>

#include "cuser/DOM.hpp"
#include "cuser/SerializerException.hpp"

namespace cuser {
namespace detail {

template <typename>
struct IsVector : std::false_type
{
};

template <typename... Args>
struct IsVector<std::vector<Args...>> : std::true_type
{
};

class VectorSerializer
{
public: // types
    template <typename T>
    using IsSupported = IsVector<T>;

public: // methods
    template <
        typename Document,
        typename Serializer,
        typename Value,
        typename... Args>
    void read(
        const InDOM<Document>& input,
        std::vector<Value, Args...>& output,
        const Serializer& serializer) const;

    template <
        typename Document,
        typename Serializer,
        typename Value,
        typename... Args>
    void write(
        const std::vector<Value, Args...>& input,
        OutDOM<Document>& output,
        Serializer& serializer);
};

template <
    typename Document,
    typename Serializer,
    typename Value,
    typename... Args>
void VectorSerializer::read(
    const InDOM<Document>& input,
    std::vector<Value, Args...>& output,
    const Serializer& serializer) const
{
    if (!input.isArray())
    {
        throw SerializerException("Isn't an array");
    }

    output.clear();
    output.reserve(input.size());
    for (std::size_t i = 0; i < input.size(); ++i)
    {
        Value value;
        serializer.read(input[i], value);
        output.push_back(std::move(value));
    }
}

template <
    typename Document,
    typename Serializer,
    typename Value,
    typename... Args>
void VectorSerializer::write(
    const std::vector<Value, Args...>& input,
    OutDOM<Document>& output,
    Serializer& serializer)
{
    output.setArray(input.size());
    for (std::size_t i = 0; i < input.size(); ++i)
    {
        auto item = output.push();
        const Value& value = input[i];
        serializer.write(value, item);
    }
}

} // namespace detail
} // namespace cuser
