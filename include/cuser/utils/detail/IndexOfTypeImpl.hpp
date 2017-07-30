#pragma once

#include <type_traits>

namespace cuser {
namespace detail {

template <typename T, std::size_t Idx, typename First, typename... Types>
struct IndexOfTypeImpl
    : std::integral_constant<
          std::size_t,
          std::is_same<T, First>::value
              ? Idx
              : IndexOfTypeImpl<T, Idx + 1, Types...>::value>
{
};

template <typename T, std::size_t Idx, typename First>
struct IndexOfTypeImpl<T, Idx, First>
    : std::integral_constant<
          std::size_t,
          std::is_same<T, First>::value ? Idx : Idx + 1>
{
};

} // namespace detail
} // namespace cuser
