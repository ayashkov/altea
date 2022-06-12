#include <iostream>

#include "test.hh"
#include "context.hh"
#include "syntax-exception.hh"

using namespace std;

namespace altea {
    Test::Test(const Location &location, Context *const context,
        const Mode mode, const string &description,
        function<void (void)> test):
        Testable(location, context, mode, description, test)
    {
    }

    void Test::addBeforeAll(const Location &location,
        function<void (void)> setup)
    {
        throw SyntaxException(location,
            "a test case cannot contain beforeAll()");
    }

    void Test::addBeforeEach(const Location &location,
        function<void (void)> setup)
    {
        throw SyntaxException(location,
            "a test case cannot contain beforeEach()");
    }

    void Test::addAfterAll(const Location &location,
        function<void (void)> teardown)
    {
        throw SyntaxException(location,
            "a test case cannot contain afterAll()");
    }

    void Test::addAfterEach(const Location &location,
        function<void (void)> teardown)
    {
        throw SyntaxException(location,
            "a test case cannot contain afterEach()");
    }

    void Test::addSuite(const Location &location, const Mode mode,
        const string &description, function<void (void)> suite)
    {
        throw SyntaxException(location,
            "a test case cannot contain describe(), fdescribe(), xdescribe()");
    }

    void Test::addTest(const Location &location, const Mode mode,
        const string &description, function<void (void)> test)
    {
        throw SyntaxException(location,
            "a test case cannot contain it(), fit(), xit()");
    }

    VoidMatcher Test::doExpect(const Location &location)
    {
        return VoidMatcher(location, this);
    }

    BoolMatcher Test::doExpect(const Location &location, const bool value)
    {
        return BoolMatcher(location, this, value);
    }

    LongMatcher Test::doExpect(const Location &location,
        const long value)
    {
        return LongMatcher(location, this, value);
    }
}
