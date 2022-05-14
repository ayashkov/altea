#include <iostream>
#include "altea.hh"

using namespace std;

namespace altea {
    Testable::Testable(Mode mode, const std::string &description,
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

    void Testable::recordFailure(const string &file, int line,
        const string &message)
    {
        failures.push_back(file + ":" + to_string(line) +": " +
            message);
    }

    void Testable::evaluate()
    {
        for (auto m : failures)
            cout << m << endl;
    }
}
