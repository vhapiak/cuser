#pragma once

#include "cuser/DOM.hpp"

#include "dom/DOMData.hpp"

namespace cuser {

template <>
class InDOM<test::DOMData>
{
public: // methods
    InDOM(const test::DOMData& data);

    bool isNull() const;
    bool isString() const;
    bool isBool() const;
    bool isInteger() const;
    bool isFloat() const;

    void getValue(std::string& str) const;
    void getValue(bool& f) const;

    template <typename Integer>
    typename std::enable_if<
        std::is_integral<Integer>::value &&
        !std::is_same<bool, Integer>::value>::type
    getValue(Integer& i) const;

    template <typename Float>
    typename std::enable_if<std::is_floating_point<Float>::value>::type
    getValue(Float& f) const;

private: // fields
    const test::DOMData& mData;
};

inline InDOM<test::DOMData>::InDOM(const test::DOMData& data)
    : mData(data)
{
}

inline bool InDOM<test::DOMData>::isNull() const
{
    return mData.isNull();
}

inline bool InDOM<test::DOMData>::isString() const
{
    return mData.isString();
}

inline bool InDOM<test::DOMData>::isBool() const
{
    return mData.isBool();
}

inline bool InDOM<test::DOMData>::isInteger() const
{
    return mData.isInteger();
}

inline bool InDOM<test::DOMData>::isFloat() const
{
    return mData.isFloat();
}

inline void InDOM<test::DOMData>::getValue(std::string& str) const
{
    str = mData.getString();
}

inline void InDOM<test::DOMData>::getValue(bool& f) const
{
    f = mData.getBool();
}

template <typename Integer>
inline typename std::enable_if<
    std::is_integral<Integer>::value &&
    !std::is_same<bool, Integer>::value>::type
InDOM<test::DOMData>::getValue(Integer& i) const
{
    i = static_cast<Integer>(mData.getInteger());
}

template <typename Float>
inline typename std::enable_if<std::is_floating_point<Float>::value>::type
InDOM<test::DOMData>::getValue(Float& f) const
{
    f = static_cast<Float>(mData.getFloat());
}

} // namespace cuser
