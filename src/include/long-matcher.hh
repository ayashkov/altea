#ifndef __LONG_MATCHER_HH
#define __LONG_MATCHER_HH

#include <string>

#include "base-matcher.hh"

namespace altea {
    class LongMatcher: public BaseMatcher {
    public:
        LongMatcher(const Location &location, Test *const test,
            const long value);

        void toBe(const long expected);

        void toBeTruthy();

        void toBeFalsy();

        LongMatcher NOT();

    private:
        const long value;

        const bool negated;

        LongMatcher(const Location &location, Test *const test,
            const long value, const bool negated);

        std::string describe(const std::string &eval, const long expected);
    };
}

#endif // __LONG_MATCHER_HH
