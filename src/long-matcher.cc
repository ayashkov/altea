#include <string>
#include "bool-matcher.hh"
#include "test.hh"

using namespace std;

namespace altea {
    LongMatcher::LongMatcher(const Location &location, Test *const test,
        const long value): BaseMatcher(location, test), value(value)
    {
    }

    void LongMatcher::toBe(long expected)
    {
        test->recordExpect();

        if (value != expected)
            test->recordFailure(location, "expected the value to be " +
                to_string(expected) + " but was " + to_string(value));
    }
}
