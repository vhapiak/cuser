#pragma once

#include <type_traits>
#include <utility>

namespace cuser {

template <typename Type>
struct GetArgByType
{
    template <typename First, typename... Args>
    static Type get(First&& first, Args&&... args);

    static Type get();

private: // static methods
    template <typename First, typename... Args>
    static Type getImpl(std::true_type&& isSame, First&& first, Args&&... args);

    template <typename First, typename... Args>
    static Type getImpl(
        std::false_type&& notSame,
        First&& first,
        Args&&... args);
};

template <typename Type>
template <typename First, typename... Args>
Type GetArgByType<Type>::get(First&& first, Args&&... args)
{
    return getImpl(
        std::is_same<Type, First>{},
        std::forward<First>(first),
        std::forward<Args>(args)...);
}

template <typename Type>
template <typename First, typename... Args>
Type GetArgByType<Type>::getImpl(
    std::true_type&& /*isSame*/,
    First&& first,
    Args&&... /*args*/)
{
    return std::forward<First>(first);
}

template <typename Type>
template <typename First, typename... Args>
Type GetArgByType<Type>::getImpl(
    std::false_type&& /*notSame*/,
    First&& /*first*/,
    Args&&... args)
{
    return get(std::forward<Args>(args)...);
}

template <typename Type>
Type GetArgByType<Type>::get()
{
    return Type{};
}

} // namespace cuser
