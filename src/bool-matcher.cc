#include "bool-matcher.hh"
#include "test.hh"

using namespace std;

namespace altea {
    BoolMatcher::BoolMatcher(const Location &location, Test *const test,
        const bool value): BaseMatcher(location, test), value(value)
    {
    }

    void BoolMatcher::toBeTrue()
    {
        test->recordExpect();

        if (!value)
            test->recordFailure(location, "expected the value to be "
                "true but was false");
    }

    void BoolMatcher::toBeFalse()
    {
        test->recordExpect();

        if (value)
            test->recordFailure(location, "expected the value to be "
                "false but was true");
    }
}
