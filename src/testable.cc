#include "altea.hh"

using namespace std;

namespace altea {
    Testable::Testable(Mode mode, std::string description,
        std::function<void (void)> testable): mode(mode),
        description(description), testable(testable)
    {
    }

    bool Testable::skipped(bool focusedMode)
    {
        return mode == EXCLUDED || (focusedMode && mode != FOCUSED);
    }

    void Testable::test()
    {
        if (testable)
            testable();
    }

    void Testable::recordExpect()
    {
        ++expectCount;
    }

    void Testable::evaluate()
    {
    }
}
