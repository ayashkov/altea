#ifndef __BOOL_MATCHER_HH
#define __BOOL_MATCHER_HH

#include "value-matcher.hh"

namespace altea {
    class BoolMatcher: public ValueMatcher<BoolMatcher, bool> {
    public:
        BoolMatcher(const Location &location, Test *const test,
            const bool value):
            BoolMatcher(location, test, false, value)
        {
        }

        BoolMatcher(const Location &location, Test *const test,
            const bool negated, const bool value):
            ValueMatcher(location, test, negated, value)
        {
        }

        inline void toBeTrue()
        {
            toBe(true);
        }

        inline void toBeFalse()
        {
            toBe(false);
        }
    };
}

#endif // __BOOL_MATCHER_HH
