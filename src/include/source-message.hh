#ifndef __SOURCE_MESSAGE_HH
#define __SOURCE_MESSAGE_HH

#include <string>

namespace altea {
    class SourceMessage {
    public:
        const std::string file;

        const int line;

        const std::string type;

        const std::string message;

        SourceMessage(const std::string &file, int line,
            const std::string &type, const std::string &message):
            file(file), line(line), type(type), message(message)
        {
        }

        operator std::string() const
        {
            return type + ": " + message + " @" + file + ":" +
                std::to_string(line);
        }
    };
}

#endif // __SOURCE_MESSAGE_HH
