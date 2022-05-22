#ifndef __SYNTAX_EXCEPTION_HH
#define __SYNTAX_EXCEPTION_HH

#include <string>
#include <exception>

#include "source-message.hh"

namespace altea {
    class SyntaxException: public std::exception {
    public:
        const std::string message;

        SyntaxException(const std::string &file, int line,
            const std::string &message): std::exception(),
            message(SourceMessage(file, line, "Syntax error", message))
        {
        }

        virtual const char *what() const noexcept
        {
            return message.c_str();
        }
    };
}

#endif // __SYNTAX_EXCEPTION_HH
