#include <iostream>

#include "testable.hh"
#include "context.hh"
#include "syntax-exception.hh"

using namespace std;

namespace altea {
    Testable::Testable(const Location &location, Context *const context,
        const Mode mode, const string &description,
        function<void (void)> testable):
        Executable(location, context, testable), mode(mode),
        description(description)
    {
    }

    bool Testable::skipped(const bool focusedMode)
    {
        return mode == EXCLUDED || (focusedMode && mode != FOCUSED);
    }

    VoidMatcher Testable::doExpect(const Location &location)
    {
        throw SyntaxException(location, "only a test can contain expect()");
    }

    BoolMatcher Testable::doExpect(const Location &location,
        const bool value)
    {
        throw SyntaxException(location, "only a test can contain expect()");
    }

    LongMatcher Testable::doExpect(const Location &location,
        const long value)
    {
        throw SyntaxException(location, "only a test can contain expect()");
    }

    void Testable::recordExpect()
    {
        ++expectCount;
    }

    void Testable::recordFailure(const Location &location,
        const string &message)
    {
        context->process(Event(location, EXPECTATION, FAIL, message));
        context->markFailed();
    }
}
