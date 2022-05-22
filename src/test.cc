#include <iostream>

#include "test.hh"
#include "context.hh"
#include "syntax-exception.hh"

using namespace std;

namespace altea {
    Test::Test(const string &file, int line, Context *context, Mode mode,
        const string &description, std::function<void (void)> test):
        Testable(file, line, context, mode, description, test)
    {
    }

    void Test::addBeforeAll(const string &file, int line,
        std::function<void (void)> setup)
    {
        throw SyntaxException(file, line,
            "a test case cannot contain beforeAll()");
    }

    void Test::addBeforeEach(const string &file, int line,
        std::function<void (void)> setup)
    {
        throw SyntaxException(file, line,
            "a test case cannot contain beforeEach()");
    }

    void Test::addAfterAll(const string &file, int line,
        std::function<void (void)> teardown)
    {
        throw SyntaxException(file, line,
            "a test case cannot contain afterAll()");
    }

    void Test::addAfterEach(const string &file, int line,
        std::function<void (void)> teardown)
    {
        throw SyntaxException(file, line,
            "a test case cannot contain afterEach()");
    }

    void Test::addSuite(const string &file, int line, Mode mode,
        const string &description, std::function<void (void)> suite)
    {
        throw SyntaxException(file, line,
            "a test case cannot contain describe(), fdescribe(), xdescribe()");
    }

    void Test::addTest(const string &file, int line, Mode mode,
        const string &description, std::function<void (void)> test)
    {
        throw SyntaxException(file, line,
            "a test case cannot contain it(), fit(), xit()");
    }

    VoidMatcher Test::doExpect(const string &file, int line)
    {
        return VoidMatcher(file, line, this);
    }

    BoolMatcher Test::doExpect(const string &file, int line, bool value)
    {
        return BoolMatcher(file, line, this, value);
    }

    void Test::evaluate() const
    {
        if (expectCount == 0)
            context->log(SourceMessage(file, line, "Warning",
                "test case '" + description + "' defines no expectations"));

        Testable::evaluate();
    }
}
