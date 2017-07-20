#pragma once

#include <istream>
#include <type_traits>

namespace cuser {
namespace detail {

template <typename T>
T& make();

template <typename T>
struct HasIstreamOpertorImpl
{
    struct Checker
    {
    };

    template <typename U>
    static auto test(U*) -> decltype(make<std::istream>() >> make<U>());
    template <typename>
    static auto test(...) -> Checker;

    using Type = std::integral_constant<
        bool,
        !std::is_same<Checker, decltype(test<T>(nullptr))>::value>;
};

template <typename T>
struct HasOstreamOpertorImpl
{
    struct Checker
    {
    };

    template <typename U>
    static auto test(U*) -> decltype(make<std::ostream>() << make<U>());
    template <typename>
    static auto test(...) -> Checker;

    using Type = std::integral_constant<
        bool,
        !std::is_same<Checker, decltype(test<T>(nullptr))>::value>;
};

} // namespace detail
} // namespace cuser
