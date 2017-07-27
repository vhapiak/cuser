#pragma once

#include <cassert>
#include <initializer_list>
#include <limits>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace cuser {
namespace test {

class DOMData
{
public: // types
    using FieldsMap = std::map<std::string, DOMData>;
    using Field = FieldsMap::value_type;
    using Iterator = FieldsMap::const_iterator;

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

    explicit DOMData(std::initializer_list<DOMData> l);
    explicit DOMData(std::initializer_list<Field> f);

    bool isNull() const;
    bool isString() const;
    bool isBool() const;
    bool isInteger() const;
    bool isFloat() const;
    bool isArray() const;
    bool isObject() const;

    std::string getString() const;
    bool getBool() const;
    int64_t getInteger() const;
    long double getFloat() const;

    std::size_t size() const;
    const DOMData& operator[](std::size_t idx) const;

    Iterator begin() const;
    Iterator end() const;

    void setString(std::string str);
    void setBool(bool f);
    void setIntger(int64_t i);
    void setFloat(long double d);

    void setArray(std::size_t size);
    DOMData& push();

    void setObject();
    DOMData& addField(std::string key);

    bool operator==(const DOMData& data) const;

private: // types
    enum Flag
    {
        Null,
        String,
        Bool,
        Integer,
        Float,
        Array,
        Object,
    };

private: // fields
    uint8_t mValueFlag;

    std::string mStringValue;
    bool mBoolValue;
    int64_t mIntegerValue;
    long double mFloatValue;
    std::vector<DOMData> mArrayValue;
    FieldsMap mObjectValue;
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

inline DOMData::DOMData(std::initializer_list<DOMData> l)
    : mValueFlag(Array)
    , mArrayValue(l)
{
}

inline DOMData::DOMData(std::initializer_list<Field> f)
    : mValueFlag(Object)
    , mObjectValue(f)
{
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

inline bool DOMData::isArray() const
{
    return mValueFlag == Array;
}

inline bool DOMData::isObject() const
{
    return mValueFlag == Object;
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

inline std::size_t DOMData::size() const
{
    assert(isArray());
    return mArrayValue.size();
}

inline const DOMData& DOMData::operator[](std::size_t idx) const
{
    assert(isArray());
    return mArrayValue[idx];
}

inline DOMData::Iterator DOMData::begin() const
{
    assert(isObject());
    return mObjectValue.begin();
}

inline DOMData::Iterator DOMData::end() const
{
    assert(isObject());
    return mObjectValue.end();
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

inline void DOMData::setArray(std::size_t size)
{
    mValueFlag = Array;
    mArrayValue.clear();
    mArrayValue.reserve(size);
}

inline DOMData& DOMData::push()
{
    assert(isArray());
    mArrayValue.push_back(DOMData());
    return mArrayValue.back();
}

inline void DOMData::setObject()
{
    mValueFlag = Object;
}

inline DOMData& DOMData::addField(std::string key)
{
    assert(isObject());
    mObjectValue.insert({key, DOMData()});
    return mObjectValue.at(key);
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
        case Array:
            return mArrayValue == data.mArrayValue;
        case Object:
            return mObjectValue == data.mObjectValue;
    }
    return false;
}

} // namespace test
} // namespace cuser
