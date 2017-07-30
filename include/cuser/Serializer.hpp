#pragma once

#include "cuser/detail/Serializer.hpp"
#include "cuser/detail/serializers/DefaultSerializer.hpp"

namespace cuser {

template <typename... Serializers>
using Serializer =
    detail::Serializer<detail::DefaultSerializer, Serializers...>;

template <typename... Serializers>
Serializer<Serializers...> makeSerializer(Serializers&&... args)
{
    return Serializer<Serializers...>(std::forward<Serializers...>(args)...);
}

} // namespace cuser
