#include <string>

#include "long-matcher.hh"

using namespace std;

namespace altea {
    LongMatcher::LongMatcher(const Location &location, Test *const test,
        const long value): LongMatcher(location, test, false, value)
    {
    }

    LongMatcher::LongMatcher(const Location &location, Test *const test,
        const bool negated, const long value):
        ValueMatcher(location, test, negated, value)
    {
    }

    void LongMatcher::toBeTruthy()
    {
        NOT().toBe(0);
    }

    void LongMatcher::toBeFalsy()
    {
        toBe(0);
    }
}
