#pragma once

#include "cuser/DOM.hpp"

#include "dom/DOMData.hpp"

namespace cuser {

template <>
class InDOM<test::DOMData>
{
public: // types
    using Item = InDOM<test::DOMData>;

    class Field
    {
    public: // types
        using Value = test::DOMData::Field;

    public: // methods
        Field(const Value& value);

        const std::string& getKey() const;
        Item getValue() const;

    private: // fields
        const Value& mValue;
    };

    class Iterator
    {
    public: // types
        using Inner = test::DOMData::Iterator;

    public: // methods
        Iterator(const Inner& it);

        bool operator!=(const Iterator& it) const;
        Iterator& operator++();
        Field operator*() const;

    private: // fields
        Inner mIt;
    };

public: // methods
    InDOM(const test::DOMData& data);

    bool isNull() const;
    bool isString() const;
    bool isBool() const;
    bool isInteger() const;
    bool isFloat() const;
    bool isArray() const;
    bool isObject() const;

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

    std::size_t size() const;
    Item operator[](std::size_t idx) const;

    Iterator begin() const;
    Iterator end() const;

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

inline bool InDOM<test::DOMData>::isArray() const
{
    return mData.isArray();
}

inline bool InDOM<test::DOMData>::isObject() const
{
    return mData.isObject();
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

inline std::size_t InDOM<test::DOMData>::size() const
{
    return mData.size();
}

inline InDOM<test::DOMData>::Item InDOM<test::DOMData>::operator[](
    std::size_t idx) const
{
    return Item(mData[idx]);
}

inline InDOM<test::DOMData>::Iterator InDOM<test::DOMData>::begin() const
{
    return Iterator(mData.begin());
}

inline InDOM<test::DOMData>::Iterator InDOM<test::DOMData>::end() const
{
    return Iterator(mData.end());
}

inline InDOM<test::DOMData>::Field::Field(const Value& value)
    : mValue(value)
{
}

inline const std::string& InDOM<test::DOMData>::Field::getKey() const
{
    return mValue.first;
}

inline InDOM<test::DOMData>::Item InDOM<test::DOMData>::Field::getValue() const
{
    return Item(mValue.second);
}

inline InDOM<test::DOMData>::Iterator::Iterator(const Inner& it)
    : mIt(it)
{
}

inline bool InDOM<test::DOMData>::Iterator::operator!=(const Iterator& it) const
{
    return mIt != it.mIt;
}

inline InDOM<test::DOMData>::Iterator& InDOM<
    test::DOMData>::Iterator::operator++()
{
    ++mIt;
    return *this;
}

inline InDOM<test::DOMData>::Field InDOM<test::DOMData>::Iterator::operator*()
    const
{
    return Field(*mIt);
}

} // namespace cuser
