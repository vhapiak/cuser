#pragma once

#include <type_traits>

#include "cuser/utils/detail/IndexOfTypeImpl.hpp"

namespace cuser {

template <typename T, typename... Types>
struct IndexOfType : detail::IndexOfTypeImpl<T, 0, Types...>
{
};

} // namespace cuser
