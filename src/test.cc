#include "altea.hh"

using namespace std;

namespace altea {
    Test::Test(bool focused, string description,
        std::function<void (void)> test): Testable(focused, description,
        test)
    {
    }

    void Test::test()
    {
        function();
    }
}
