#pragma once

#include "cuser/utils/detail/LastIndexOfImpl.hpp"

namespace cuser {

template <typename T, T Value, T First, T... Args>
struct LastIndexOf
    : detail::LastIndexOfImpl<
          sizeof...(Args) == 0,
          T,
          Value,
          0,
          sizeof...(Args) + 1,
          First,
          Args...>
{
};

} // namespace cuser
