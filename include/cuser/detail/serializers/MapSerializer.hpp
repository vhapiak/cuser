#pragma once

#include <map>
#include <sstream>
#include <type_traits>

#include "cuser/DOM.hpp"
#include "cuser/SerializerException.hpp"
#include "cuser/utils/HasStreamOperators.hpp"

namespace cuser {
namespace detail {

template <typename>
struct IsMap : std::false_type
{
};

template <typename Key, typename... Args>
struct IsMap<std::map<Key, Args...>>
    : std::integral_constant<
          bool,
          HasOstreamOperator<Key>::value || HasIstreamOperator<Key>::value>
{
};

class MapSerializer
{
public: // types
    template <typename T>
    using IsSupported = IsMap<T>;

public: // methods
    template <
        typename Document,
        typename Serializer,
        typename Key,
        typename Value,
        typename... Args>
    void read(
        const InDOM<Document>& input,
        std::map<Key, Value, Args...>& output,
        const Serializer& serializer) const;

    template <
        typename Document,
        typename Serializer,
        typename Key,
        typename... Args>
    void write(
        const std::map<Key, Args...>& input,
        OutDOM<Document>& output,
        Serializer& serializer);
};

template <
    typename Document,
    typename Serializer,
    typename Key,
    typename Value,
    typename... Args>
void MapSerializer::read(
    const InDOM<Document>& input,
    std::map<Key, Value, Args...>& output,
    const Serializer& serializer) const
{
    static_assert(
        HasIstreamOperator<Key>::value, "Key doesn't has istream operator");
    if (!input.isObject())
    {
        throw SerializerException("Isn't an object");
    }

    for (const auto& field : input)
    {
        Key key;
        std::stringstream ss(field.getKey());
        ss >> key;

        Value value;
        serializer.read(field.getValue(), value);

        output.insert({std::move(key), std::move(value)});
    }
}

template <
    typename Document,
    typename Serializer,
    typename Key,
    typename... Args>
void MapSerializer::write(
    const std::map<Key, Args...>& input,
    OutDOM<Document>& output,
    Serializer& serializer)
{
    static_assert(
        HasOstreamOperator<Key>::value, "Key doesn't has ostream operator");

    output.setObject();
    for (auto& item : input)
    {
        std::stringstream ss;
        ss << item.first;
        if (ss.fail())
        {
            throw SerializerException("Cannot serialize key");
        }
        auto field = output.addField(ss.str());
        serializer.write(item.second, field);
    }
}

} // namespace detail
} // namespace cuser
