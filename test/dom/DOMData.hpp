#pragma once

#include <cassert>
#include <limits>
#include <string>
#include <type_traits>

namespace cuser {
namespace test {

class DOMData
{
public: // methods
    explicit DOMData();
    explicit DOMData(std::string str);
    explicit DOMData(bool f);

    template <
        typename Integer,
        typename = typename std::enable_if<
            std::is_integral<Integer>::value &&
            !std::is_same<bool, Integer>::value>::type,
        int = 0>
    explicit DOMData(Integer i)
    {
        setIntger(i);
    }

    template <
        typename Float,
        typename =
            typename std::enable_if<std::is_floating_point<Float>::value>::type>
    explicit DOMData(Float d)
    {
        setFloat(d);
    }

    bool isNull() const;
    bool isString() const;
    bool isBool() const;
    bool isInteger() const;
    bool isFloat() const;

    std::string getString() const;
    bool getBool() const;
    int64_t getInteger() const;
    long double getFloat() const;

    void setString(std::string str);
    void setBool(bool f);
    void setIntger(int64_t i);
    void setFloat(long double d);

    bool operator==(const DOMData& data) const;

private: // types
    enum Flag
    {
        Null,
        String,
        Bool,
        Integer,
        Float,
    };

private: // fields
    uint8_t mValueFlag;

    std::string mStringValue;
    bool mBoolValue;
    int64_t mIntegerValue;
    long double mFloatValue;
};

inline DOMData::DOMData()
    : mValueFlag(Null)
{
}

inline DOMData::DOMData(std::string str)
{
    setString(str);
}

inline DOMData::DOMData(bool f)
{
    setBool(f);
}

inline bool DOMData::isNull() const
{
    return mValueFlag == Null;
}

inline bool DOMData::isString() const
{
    return mValueFlag == String;
}

inline bool DOMData::isBool() const
{
    return mValueFlag == Bool;
}

inline bool DOMData::isInteger() const
{
    return mValueFlag == Integer;
}

inline bool DOMData::isFloat() const
{
    return mValueFlag == Float;
}

inline std::string DOMData::getString() const
{
    assert(isString());
    return mStringValue;
}

inline bool DOMData::getBool() const
{
    assert(isBool());
    return mBoolValue;
}

inline int64_t DOMData::getInteger() const
{
    assert(isInteger());
    return mIntegerValue;
}

inline long double DOMData::getFloat() const
{
    assert(isFloat());
    return mFloatValue;
}

inline void DOMData::setString(std::string str)
{
    mValueFlag = String;
    mStringValue = str;
}

inline void DOMData::setBool(bool f)
{
    mValueFlag = Bool;
    mBoolValue = f;
}

inline void DOMData::setIntger(int64_t i)
{
    mValueFlag = Integer;
    mIntegerValue = i;
}

inline void DOMData::setFloat(long double d)
{
    mValueFlag = Float;
    mFloatValue = d;
}

inline bool DOMData::operator==(const DOMData& data) const
{
    if (mValueFlag != data.mValueFlag)
    {
        return false;
    }

    switch (mValueFlag)
    {
        case Null:
            return true;
        case String:
            return mStringValue == data.mStringValue;
        case Bool:
            return mBoolValue == data.mBoolValue;
        case Integer:
            return mIntegerValue == data.mIntegerValue;
        case Float:
            return std::abs(mFloatValue - data.mFloatValue) <=
                   std::numeric_limits<decltype(mFloatValue)>::epsilon();
    }
    return false;
}

} // namespace test
} // namespace cuser
