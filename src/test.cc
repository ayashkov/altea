#include "altea.hh"

using namespace std;

namespace altea {
    Test::Test(string d, std::function<void (void)> t): Testable(d, t)
    {
    }

    void Test::test()
    {
        if (function)
            function();
    }
}
