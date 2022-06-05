#include "void-matcher.hh"
#include "test.hh"

using namespace std;

namespace altea {
    VoidMatcher::VoidMatcher(const Location &location, Test *const test):
        BaseMatcher(location, test)
    {
    }

    void VoidMatcher::nothing()
    {
        test->recordExpect();
    }

    void VoidMatcher::toFail(const string &message)
    {
        test->recordExpect();
        test->recordFailure(location, message);
    }
}
