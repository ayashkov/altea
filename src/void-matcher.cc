#include "void-matcher.hh"
#include "test.hh"

using namespace std;

namespace altea {
    VoidMatcher::VoidMatcher(const string &file, int line, Test *test):
        BaseMatcher(file, line, test)
    {
    }

    void VoidMatcher::nothing()
    {
        test->recordExpect();
    }

    void VoidMatcher::toFail(const string &message)
    {
        test->recordExpect();
        test->recordFailure(file, line, message);
    }
}
