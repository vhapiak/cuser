#pragma once

#include <tuple>

#include "cuser/DOM.hpp"
#include "cuser/utils/LastIndexOf.hpp"

namespace cuser {
namespace detail {

template <typename... Serializers>
class Serializer
{
public: // methods
    template <typename Document, typename Data>
    void read(const InDOM<Document>& input, Data& output) const;

    template <typename Document, typename Data>
    void read(const Document& input, Data& output) const;

    template <typename Data, typename Document>
    void write(const Data& input, OutDOM<Document>& output);

    template <typename Data, typename Document>
    void write(const Data& input, Document& output);

private: // fields
    std::tuple<Serializers...> mSerializers;
};

template <typename... Serializers>
template <typename Document, typename Data>
void Serializer<Serializers...>::read(
    const InDOM<Document>& input,
    Data& output) const
{
    constexpr std::size_t serializerIdx = cuser::LastIndexOf<
        bool,
        true,
        Serializers::template IsSupported<Data>::value...>::value;
    static_assert(
        serializerIdx < sizeof...(Serializers), "Serializer not found");

    std::get<serializerIdx>(mSerializers).read(input, output, *this);
}

template <typename... Serializers>
template <typename Document, typename Data>
void Serializer<Serializers...>::read(const Document& input, Data& output)
    const
{
    InDOM<Document> dom(input);
    read(dom, output);
}

template <typename... Serializers>
template <typename Data, typename Document>
void Serializer<Serializers...>::write(
    const Data& input,
    OutDOM<Document>& output)
{
    constexpr std::size_t serializerIdx = cuser::LastIndexOf<
        bool,
        true,
        Serializers::template IsSupported<Data>::value...>::value;
    static_assert(
        serializerIdx < sizeof...(Serializers), "Deserializer not found");

    std::get<serializerIdx>(mSerializers).write(input, output, *this);
}

template <typename... Serializers>
template <typename Data, typename Document>
void Serializer<Serializers...>::write(const Data& input, Document& output)
{
    OutDOM<Document> dom(output);
    write(input, dom);
}

} // namespace detail
} // namespace cuser
