#include "bool-matcher.hh"

using namespace std;

namespace altea {
    BoolMatcher::BoolMatcher(const Location &location, Test *const test,
        const bool value): BoolMatcher(location, test, value, false)
    {
    }

    BoolMatcher::BoolMatcher(const Location &location, Test *const test,
        const bool value, const bool negated): BaseMatcher(location, test),
        value(value), negated(negated)
    {
    }

    void BoolMatcher::toBe(const bool expected)
    {
        recordExpect();

        if ((value == expected) == negated)
            recordFailure(describe("to be", expected));
    }

    void BoolMatcher::toBeTrue()
    {
        toBe(true);
    }

    void BoolMatcher::toBeFalse()
    {
        toBe(false);
    }

    BoolMatcher BoolMatcher::NOT()
    {
        return BoolMatcher(location, test, value, !negated);
    }

    string BoolMatcher::describe(const string &eval, const bool expected)
    {
        string d = "expected the value ";

        if (negated)
            d += "NOT ";

        d += eval + " " + to_string(expected) + ", but it was " +
            to_string(value);

        return d;
    }
}
