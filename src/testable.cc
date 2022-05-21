#include <iostream>
#include "altea.hh"

using namespace std;

namespace altea {
    Testable::Testable(const string &file, int line, Context *context,
        Mode mode, const std::string &description,
        std::function<void (void)> testable): file(file), line(line),
        context(context), mode(mode), description(description),
        testable(testable)
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
        failures.push_back(SourceMessage(file, line, "Failure", message));
        context->markFailed();
    }

    void Testable::evaluate() const
    {
        for (auto m : failures)
            context->log(m);
    }
}
