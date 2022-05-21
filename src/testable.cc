#include <iostream>
#include "altea.hh"

using namespace std;

namespace altea {
    Testable::Testable(const string &file, int line, Mode mode,
        const std::string &description,
        std::function<void (void)> testable): file(file), line(line),
        mode(mode), description(description), testable(testable)
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

    void Testable::addFailure(SourceMessage &failure)
    {
        failures.push_back(failure);
    }

    void Testable::evaluate() const
    {
        for (auto m : failures)
            __context__.log(m);
    }
}
