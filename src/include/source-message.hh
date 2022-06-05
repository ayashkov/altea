#ifndef __SOURCE_MESSAGE_HH
#define __SOURCE_MESSAGE_HH

#include <string>

#include "location.hh"

namespace altea {
    class SourceMessage {
    public:
        const Location location;

        const std::string type;

        const std::string message;

        SourceMessage(const Location &location, const std::string &type,
            const std::string &message): location(location), type(type),
            message(message)
        {
        }

        operator std::string() const
        {
            return type + ": " + message + " " + (std::string)location;
        }
    };
}

#endif // __SOURCE_MESSAGE_HH
