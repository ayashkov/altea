#include "base-matcher.hh"
#include "test.hh"

using namespace std;

namespace altea {
    BaseMatcher::BaseMatcher(const Location &location, Test *const test):
        location(location), test(test)
    {
    }

    void BaseMatcher::recordExpect()
    {
        test->recordExpect();
    }

    void BaseMatcher::recordFailure(const string &message)
    {
        test->recordFailure(location, message);
    }
}
