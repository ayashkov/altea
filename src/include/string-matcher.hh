#ifndef __STRING_MATCHER_HH
#define __STRING_MATCHER_HH

#include <string>

#include "value-matcher.hh"

namespace altea {
    class StringMatcher: public ValueMatcher<StringMatcher, std::string> {
    public:
        StringMatcher(const Location &location, Test *const test,
            const std::string &value):
            StringMatcher(location, test, false, value)
        {
        }

        StringMatcher(const Location &location, Test *const test,
            const bool negated, const std::string &value):
            ValueMatcher(location, test, negated, value)
        {
        }
    };
}

#endif // __STRING_MATCHER_HH
