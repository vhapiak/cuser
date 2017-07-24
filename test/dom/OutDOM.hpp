#pragma once

#include "cuser/DOM.hpp"

#include "dom/DOMData.hpp"

namespace cuser {

template <>
class OutDOM<test::DOMData>
{
public: // methods
    OutDOM(test::DOMData& data);

    void setValue(std::string str);

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

} // namespace cuser
