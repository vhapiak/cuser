#pragma once

#include <json.hpp>

#include "cuser/DOM.hpp"

namespace cuser {

template <>
class InDOM<nlohmann::json>
{
public: // types
    using Item = InDOM<nlohmann::json>;

    class Field
    {
    public: // types
        using Value = nlohmann::json::const_iterator;

    public: // methods
        Field(const Value& value);

        std::string getKey() const;
        Item getValue() const;

    private: // fields
        const Value& mValue;
    };

    class Iterator
    {
    public: // types
        using Inner = nlohmann::json::const_iterator;

    public: // methods
        Iterator(const Inner& it);

        bool operator!=(const Iterator& it) const;
        Iterator& operator++();
        Field operator*() const;

    private: // fields
        Inner mIt;
    };

public: // methods
    InDOM(const nlohmann::json& data);

    bool isNull() const;
    bool isString() const;
    bool isBool() const;
    bool isInteger() const;
    bool isFloat() const;
    bool isArray() const;
    bool isObject() const;

    template <typename T>
    void getValue(T& value) const;

    std::size_t size() const;
    Item operator[](std::size_t idx) const;

    Iterator begin() const;
    Iterator end() const;

private: // fields
    const nlohmann::json& mData;
};

inline InDOM<nlohmann::json>::InDOM(const nlohmann::json& data)
    : mData(data)
{
}

inline bool InDOM<nlohmann::json>::isNull() const
{
    return mData.is_null();
}

inline bool InDOM<nlohmann::json>::isString() const
{
    return mData.is_string();
}

inline bool InDOM<nlohmann::json>::isBool() const
{
    return mData.is_boolean();
}

inline bool InDOM<nlohmann::json>::isInteger() const
{
    return mData.is_number_integer() || mData.is_number_unsigned();
}

inline bool InDOM<nlohmann::json>::isFloat() const
{
    return mData.is_number_float();
}

inline bool InDOM<nlohmann::json>::isArray() const
{
    return mData.is_array();
}

inline bool InDOM<nlohmann::json>::isObject() const
{
    return mData.is_object();
}

template <typename T>
inline void InDOM<nlohmann::json>::getValue(T& value) const
{
    value = mData;
}

inline std::size_t InDOM<nlohmann::json>::size() const
{
    return mData.size();
}

inline InDOM<nlohmann::json>::Item InDOM<nlohmann::json>::operator[](
    std::size_t idx) const
{
    return Item(mData[idx]);
}

inline InDOM<nlohmann::json>::Iterator InDOM<nlohmann::json>::begin() const
{
    return Iterator(mData.begin());
}

inline InDOM<nlohmann::json>::Iterator InDOM<nlohmann::json>::end() const
{
    return Iterator(mData.end());
}

inline InDOM<nlohmann::json>::Field::Field(const Value& value)
    : mValue(value)
{
}

inline std::string InDOM<nlohmann::json>::Field::getKey() const
{
    return mValue.key();
}

inline InDOM<nlohmann::json>::Item InDOM<nlohmann::json>::Field::getValue()
    const
{
    return Item(mValue.value());
}

inline InDOM<nlohmann::json>::Iterator::Iterator(const Inner& it)
    : mIt(it)
{
}

inline bool InDOM<nlohmann::json>::Iterator::operator!=(
    const Iterator& it) const
{
    return mIt != it.mIt;
}

inline InDOM<nlohmann::json>::Iterator& InDOM<
    nlohmann::json>::Iterator::operator++()
{
    ++mIt;
    return *this;
}

inline InDOM<nlohmann::json>::Field InDOM<nlohmann::json>::Iterator::operator*()
    const
{
    return Field(mIt);
}

} // namespace cuser
