#pragma once

#include "cuser/DOM.hpp"

namespace cuser {
namespace detail {

class Serializer
{
public: // methods
    template <typename Underlying, typename Data>
    void read(const InDOM<Underlying>& input, Data& output);

    template <typename Underlying, typename Data>
    void read(const Underlying& input, Data& output);

    template <typename Data, typename Underlying>
    void write(const Data& input, OutDOM<Underlying>& output);

    template <typename Data, typename Underlying>
    void write(const Data& input, Underlying& output);
};

template <typename Underlying, typename Data>
void Serializer::read(const InDOM<Underlying>& /*input*/, Data& /*output*/)
{
}

template <typename Underlying, typename Data>
void Serializer::read(const Underlying& input, Data& output)
{
    InDOM<Underlying> dom(input);
    read(dom, output);
}

template <typename Data, typename Underlying>
void Serializer::write(const Data& /*input*/, OutDOM<Underlying>& /*output*/)
{
}

template <typename Data, typename Underlying>
void Serializer::write(const Data& input, Underlying& output)
{
    OutDOM<Underlying> dom(output);
    write(input, dom);
}

} // namespace detail
} // namespace cuser
