#pragma once

#include <cstddef>
#include <type_traits>

namespace cuser {
namespace detail {

template <
    bool Terminate,
    typename T,
    T Value,
    std::size_t Idx,
    std::size_t Res,
    T First,
    T... Args>
struct LastIndexOfImpl
    : std::integral_constant<
          std::size_t,
          LastIndexOfImpl<
              sizeof...(Args) == 1,
              T,
              Value,
              Idx + 1,
              Value == First ? Idx : Res,
              Args...>::value>
{
};

template <typename T, T Value, std::size_t Idx, std::size_t Res, T First>
struct LastIndexOfImpl<true, T, Value, Idx, Res, First>
    : std::integral_constant<std::size_t, Value == First ? Idx : Res>
{
};

} // namespace detail
} // namespace cuser
