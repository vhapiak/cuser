#pragma once

#include <stdexcept>

namespace cuser {

class SerializerException : public std::runtime_error
{
public: // methods
    SerializerException(const std::string& what)
        : std::runtime_error(what)
    {
    }

    SerializerException(const char* msg)
        : std::runtime_error(msg)
    {
    }
};

} // namespace cuser
