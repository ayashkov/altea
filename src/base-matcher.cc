#include "base-matcher.hh"

using namespace std;

namespace altea {
    BaseMatcher::BaseMatcher(const string &file, int line, Test *test):
        file(file), line(line), test(test)
    {
    }
}
