#ifndef __BOOL_MATCHER_HH
#define __BOOL_MATCHER_HH

#include <string>

#include "value-matcher.hh"

namespace altea {
    class BoolMatcher: public ValueMatcher<BoolMatcher, bool> {
    public:
        BoolMatcher(const Location &location, Test *const test,
            const bool value);

        BoolMatcher(const Location &location, Test *const test,
            const bool negated, const bool value);

        void toBeTrue();

        void toBeFalse();
    };
}

#endif // __BOOL_MATCHER_HH
