#pragma once

#include <json.hpp>

#include "cuser/DOM.hpp"

namespace cuser {

template <>
class OutDOM<nlohmann::json>
{
public: // types
    using Item = OutDOM<nlohmann::json>;

public: // methods
    OutDOM(nlohmann::json& data);

    template <typename T>
    void setValue(T value);

    void setArray(std::size_t size);
    Item push();

    void setObject();
    Item addField(std::string key);

private: // fields
    nlohmann::json& mData;
};

inline OutDOM<nlohmann::json>::OutDOM(nlohmann::json& data)
    : mData(data)
{
}

template <typename T>
inline void OutDOM<nlohmann::json>::setValue(T value)
{
    mData = std::move(value);
}

inline void OutDOM<nlohmann::json>::setArray(std::size_t /*size*/)
{
    mData = nlohmann::json::value_t::array;
}

inline OutDOM<nlohmann::json>::Item OutDOM<nlohmann::json>::push()
{
    mData += nlohmann::json();
    return Item(mData.back());
}

inline void OutDOM<nlohmann::json>::setObject()
{
    mData = nlohmann::json::value_t::object;
}

inline OutDOM<nlohmann::json>::Item OutDOM<nlohmann::json>::addField(
    std::string key)
{
    return Item(mData[key]);
}

} // namespace cuser
