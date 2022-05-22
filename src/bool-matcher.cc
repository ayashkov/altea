#include "bool-matcher.hh"
#include "test.hh"

using namespace std;

namespace altea {
    BoolMatcher::BoolMatcher(const string &file, int line, Test *test,
        bool value): BaseMatcher(file, line, test), value(value)
    {
    }

    void BoolMatcher::toBeTrue()
    {
        test->recordExpect();

        if (!value)
            test->recordFailure(file, line, "expected the value to be "
                "true but was false");
    }

    void BoolMatcher::toBeFalse()
    {
        test->recordExpect();

        if (value)
            test->recordFailure(file, line, "expected the value to be "
                "false but was true");
    }
}
