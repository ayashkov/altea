#ifndef __LONG_MATCHER_HH
#define __LONG_MATCHER_HH

#include <string>

#include "value-matcher.hh"

namespace altea {
    class LongMatcher: public ValueMatcher<LongMatcher, long> {
    public:
        LongMatcher(const Location &location, Test *const test,
            const long value);

        LongMatcher(const Location &location, Test *const test,
            const bool negated, const long value);

        void toBeTruthy();

        void toBeFalsy();
    };
}

#endif // __LONG_MATCHER_HH
