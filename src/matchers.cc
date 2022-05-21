#include "altea.hh"

using namespace std;

namespace altea {
    VoidMatcher::VoidMatcher(const string &file, int line, Test *test):
        file(file), line(line), test(test)
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
}
