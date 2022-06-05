#include "base-matcher.hh"

using namespace std;

namespace altea {
    BaseMatcher::BaseMatcher(const Location &location, Test *const test):
        location(location), test(test)
    {
    }
}
