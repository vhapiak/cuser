#pragma once

#include <type_traits>

#include "cuser/DOM.hpp"
#include "cuser/detail/Serializer.hpp"
#include "cuser/detail/serializers/ArraySerializer.hpp"
#include "cuser/detail/serializers/BoolSerializer.hpp"
#include "cuser/detail/serializers/FloatSerializer.hpp"
#include "cuser/detail/serializers/IOStreamSerializer.hpp"
#include "cuser/detail/serializers/IntegerSerializer.hpp"
#include "cuser/detail/serializers/MapSerializer.hpp"
#include "cuser/detail/serializers/VectorSerializer.hpp"

namespace cuser {
namespace detail {

class DefaultSerializer
{
public: // types
    template <typename T>
    using IsSupported = std::true_type;

public: // methods
    template <typename Document, typename Output, typename Serializer>
    void read(
        const InDOM<Document>& input,
        Output& output,
        const Serializer& serializer) const;

    template <typename Document, typename Input, typename Serializer>
    void write(
        const Input& input,
        OutDOM<Document>& output,
        Serializer& serializer);

private: // fields
    Serializer<
        IOStreamSerializer,
        BoolSerializer,
        IntegerSerializer,
        FloatSerializer,
        ArraySerializer,
        VectorSerializer,
        MapSerializer>
        m_serializer;
};

template <typename Document, typename Output, typename Serializer>
void DefaultSerializer::read(
    const InDOM<Document>& input,
    Output& output,
    const Serializer& serializer) const
{
    m_serializer.read(input, output, serializer);
}

template <typename Document, typename Input, typename Serializer>
void DefaultSerializer::write(
    const Input& input,
    OutDOM<Document>& output,
    Serializer& serializer)
{
    m_serializer.write(input, output, serializer);
}

} // namespace detail
} // namespace cuser
