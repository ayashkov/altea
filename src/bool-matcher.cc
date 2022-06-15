#include "bool-matcher.hh"

using namespace std;

namespace altea {
    BoolMatcher::BoolMatcher(const Location &location, Test *const test,
        const bool value): BoolMatcher(location, test, false, value)
    {
    }

    BoolMatcher::BoolMatcher(const Location &location, Test *const test,
        const bool negated, const bool value):
        ValueMatcher(location, test, negated, value)
    {
    }

    void BoolMatcher::toBeTrue()
    {
        toBe(true);
    }

    void BoolMatcher::toBeFalse()
    {
        toBe(false);
    }
}
