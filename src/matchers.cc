#include "altea.hh"

using namespace std;

namespace altea {
    BaseMatcher::BaseMatcher(const string &file, int line, Test *test):
        file(file), line(line), test(test)
    {
    }

    VoidMatcher::VoidMatcher(const string &file, int line, Test *test):
        BaseMatcher(file, line, test)
    {
    }

    void VoidMatcher::nothing()
    {
        test->recordExpect();
    }

    void VoidMatcher::toFail(const std::string &message)
    {
        test->recordExpect();
        test->recordFailure(file, line, message);
    }

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
