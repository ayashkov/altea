#ifndef __LONG_MATCHER_HH
#define __LONG_MATCHER_HH

#include "value-matcher.hh"

namespace altea {
    class LongMatcher: public ValueMatcher<LongMatcher, long> {
    public:
        LongMatcher(const Location &location, Test *const test,
            const long value): LongMatcher(location, test, false, value)
        {
        }

        LongMatcher(const Location &location, Test *const test,
            const bool negated, const long value):
            ValueMatcher(location, test, negated, value)
        {
        }

        inline void toBeTruthy()
        {
            NOT().toBeFalsy();
        }

        inline void toBeFalsy()
        {
            toBe(0);
        }
    };
}

#endif // __LONG_MATCHER_HH
