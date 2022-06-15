#include "void-matcher.hh"

using namespace std;

namespace altea {
    VoidMatcher::VoidMatcher(const Location &location, Test *const test):
        BaseMatcher(location, test)
    {
    }

    void VoidMatcher::nothing()
    {
        recordExpect();
    }

    void VoidMatcher::toFail(const string &message)
    {
        recordExpect();
        recordFailure(message);
    }
}
