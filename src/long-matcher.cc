#include <string>

#include "long-matcher.hh"

using namespace std;

namespace altea {
    LongMatcher::LongMatcher(const Location &location, Test *const test,
        const long value): LongMatcher(location, test, value, false)
    {
    }

    LongMatcher::LongMatcher(const Location &location, Test *const test,
        const long value, const bool negated): BaseMatcher(location, test),
        value(value), negated(negated)
    {
    }

    void LongMatcher::toBe(const long expected)
    {
        recordExpect();

        if ((value == expected) == negated)
            recordFailure(describe("to be", expected));
    }

    void LongMatcher::toBeTruthy()
    {
        NOT().toBe(0);
    }

    void LongMatcher::toBeFalsy()
    {
        toBe(0);
    }

    LongMatcher LongMatcher::NOT()
    {
        return LongMatcher(location, test, value, !negated);
    }

    string LongMatcher::describe(const string &eval, const long expected)
    {
        string d = "expected the value ";

        if (negated)
            d += "NOT ";

        d += eval + " " + to_string(expected) + ", but it was " +
            to_string(value);

        return d;
    }
}
