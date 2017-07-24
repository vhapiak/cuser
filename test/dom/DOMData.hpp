#pragma once

#include <cassert>
#include <string>

namespace cuser {
namespace test {

class DOMData
{
public: // methods
    DOMData();
    DOMData(std::string str);

    bool isNull() const;
    bool isString() const;

    std::string getString() const;

    void setString(std::string str);

    bool operator==(const DOMData& data) const;

private: // types
    enum Flag
    {
        Null,
        String,
    };

private: // fields
    uint8_t mValueFlag;
    std::string mStringValue;
};

inline DOMData::DOMData()
    : mValueFlag(Null)
{
}

inline DOMData::DOMData(std::string str)
{
    setString(str);
}

inline bool DOMData::isNull() const
{
    return mValueFlag == Null;
}

inline bool DOMData::isString() const
{
    return mValueFlag == String;
}

inline std::string DOMData::getString() const
{
    assert(mValueFlag == String);
    return mStringValue;
}

inline void DOMData::setString(std::string str)
{
    mValueFlag = String;
    mStringValue = str;
}

bool DOMData::operator==(const DOMData& data) const
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
    }
    return false;
}

} // namespace test
} // namespace cuser
