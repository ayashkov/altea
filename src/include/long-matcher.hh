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

    private:
        const long value;
    };
}

#endif // __LONG_MATCHER_HH
