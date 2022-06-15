#ifndef __BOOL_MATCHER_HH
#define __BOOL_MATCHER_HH

#include <string>

#include "base-matcher.hh"

namespace altea {
    class BoolMatcher: public BaseMatcher {
    public:
        BoolMatcher(const Location &location, Test *const test,
            const bool value);

        void toBe(const bool expected);

        void toBeTrue();

        void toBeFalse();

        BoolMatcher NOT();

    private:
        const bool value;

        const bool negated;

        BoolMatcher(const Location &location, Test *const test,
            const bool value, const bool negated);

        std::string describe(const std::string &eval, const bool expected);
    };
}

#endif // __BOOL_MATCHER_HH
