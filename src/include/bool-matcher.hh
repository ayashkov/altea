#ifndef __BOOL_MATCHER_HH
#define __BOOL_MATCHER_HH

#include <string>

#include "base-matcher.hh"

namespace altea {
    class BoolMatcher: public BaseMatcher {
    public:
        BoolMatcher(const Location &location, Test *const test,
            const bool value);

        void toBeTrue();

        void toBeFalse();

    private:
        const bool value;
    };
}

#endif // __BOOL_MATCHER_HH
