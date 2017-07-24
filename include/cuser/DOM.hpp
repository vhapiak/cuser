#pragma once

#include <string>

namespace cuser {

template <typename Document>
class InDOM
{
public: // types
    InDOM(const Document& doc);

    bool isNull() const;
    bool isString() const;

    void getValue(std::string& str) const;
};

template <typename Document>
class OutDOM
{
public: // types
    OutDOM(Document& doc);

    void setValue(std::string str);
};

} // namespace cuser
