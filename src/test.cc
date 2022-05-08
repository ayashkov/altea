#include "altea.hh"

using namespace std;

namespace altea {
    Test::Test(Mode mode, string description,
        std::function<void (void)> test): Testable(mode, description,
        test)
    {
    }

    void Test::test()
    {
        if (testable)
            testable();
    }
}
