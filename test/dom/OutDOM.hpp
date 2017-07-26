#pragma once

#include "cuser/DOM.hpp"

#include "dom/DOMData.hpp"

namespace cuser {

template <>
class OutDOM<test::DOMData>
{
public: // types
    using Item = OutDOM<test::DOMData>;

public: // methods
    OutDOM(test::DOMData& data);

    void setValue(std::string str);
    void setValue(bool f);

    template <typename Integer>
    typename std::enable_if<
        std::is_integral<Integer>::value &&
        !std::is_same<bool, Integer>::value>::type
    setValue(Integer i);

    template <typename Float>
    typename std::enable_if<std::is_floating_point<Float>::value>::type
    setValue(Float f);

    void setArray(std::size_t size);
    Item push();

private: // fields
    test::DOMData& mData;
};

inline OutDOM<test::DOMData>::OutDOM(test::DOMData& data)
    : mData(data)
{
}

inline void OutDOM<test::DOMData>::setValue(std::string str)
{
    mData.setString(str);
}

inline void OutDOM<test::DOMData>::setValue(bool f)
{
    mData.setBool(f);
}

template <typename Integer>
inline typename std::enable_if<
    std::is_integral<Integer>::value &&
    !std::is_same<bool, Integer>::value>::type
OutDOM<test::DOMData>::setValue(Integer i)
{
    mData.setIntger(i);
}

template <typename Float>
inline typename std::enable_if<std::is_floating_point<Float>::value>::type
OutDOM<test::DOMData>::setValue(Float f)
{
    mData.setFloat(f);
}

inline void OutDOM<test::DOMData>::setArray(std::size_t size)
{
    mData.setArray(size);
}

inline OutDOM<test::DOMData>::Item OutDOM<test::DOMData>::push()
{
    return Item(mData.push());
}

} // namespace cuser
