#pragma once

#include "cuser/utils/detail/HasStreamOperatorsImpl.hpp"

namespace cuser {

template <typename T>
struct HasIstreamOperator : detail::HasIstreamOpertorImpl<T>::Type
{
};

template <typename T>
struct HasOstreamOperator : detail::HasOstreamOpertorImpl<T>::Type
{
};

} // namespace cuser
