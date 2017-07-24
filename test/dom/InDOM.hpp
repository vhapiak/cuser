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

    void getValue(std::string& str) const;

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

inline void InDOM<test::DOMData>::getValue(std::string& str) const
{
    str = mData.getString();
}

} // namespace cuser
