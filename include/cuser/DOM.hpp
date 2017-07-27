#pragma once

#include <string>
#include <type_traits>

namespace cuser {

template <typename Document>
class InDOM
{
public: // types
    using Item = InDOM<Document>;

    class Field
    {
    public:
        const std::string& getKey() const;
        Item getValue() const;
    };

    struct Iterator
    {
        bool operator!=(const Iterator&) const;
        Iterator& operator++() const;
        const Field& operator*() const;
    };

public: // methods
    InDOM(const Document& doc);

    bool isNull() const;
    bool isString() const;
    bool isBool() const;
    bool isInteger() const;
    bool isFloat() const;
    bool isArray() const;
    bool isObject() const;

    void getValue(std::string& str) const;

    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type getValue(
        T& value) const;

    std::size_t size() const;
    Item operator[](std::size_t idx) const;

    Iterator begin() const;
    Iterator end() const;
};

template <typename Document>
class OutDOM
{
public: // types
    using Item = InDOM<Document>;

public: // methods
    OutDOM(Document& doc);

    void setValue(std::string str);
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type setValue(
        T value);

    void setArray(std::size_t size);
    Item push();

    void setObject();
    Item addField(std::string key);
};

} // namespace cuser
