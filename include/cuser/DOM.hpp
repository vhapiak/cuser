#pragma once

#include <string>
#include <type_traits>

namespace cuser {

template <typename Document>
class InDOM
{
public: // types
    InDOM(const Document& doc);

    bool isNull() const;
    bool isString() const;
    bool isBool() const;
    bool isInteger() const;
    bool isFloat() const;

    void getValue(std::string& str) const;

    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type getValue(
        T& value) const;
};

template <typename Document>
class OutDOM
{
public: // types
    OutDOM(Document& doc);

    void setValue(std::string str);
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type setValue(
        T value);
};

} // namespace cuser
