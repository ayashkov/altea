#include <iostream>
#include "altea.hh"

using namespace std;

namespace altea {
    Test::Test(const string &file, int line, Mode mode,
        const string &description, std::function<void (void)> test):
        Testable(file, line, mode, description, test)
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

    Matcher Test::doExpect(const string &file, int line) const
    {
        return Matcher(file, line);
    }

    void Test::evaluate() const
    {
        if (expectCount == 0)
            __context__.log(SourceMessage(file, line, "Warning",
                "test case '" + description + "' defines no expectations"));

        Testable::evaluate();
    }
}
