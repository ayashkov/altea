#include <iostream>
#include "altea.hh"

using namespace std;

namespace altea {
    Test::Test(Mode mode, string description,
        std::function<void (void)> test): Testable(mode, description,
        test)
    {
    }

    void Test::addBeforeAll(std::function<void (void)> setup)
    {
        throw SyntaxException("a test case cannot contain beforeAll()");
    }

    void Test::addBeforeEach(std::function<void (void)> setup)
    {
        throw SyntaxException("a test case cannot contain beforeEach()");
    }

    void Test::addAfterAll(std::function<void (void)> teardown)
    {
        throw SyntaxException("a test case cannot contain afterAll()");
    }

    void Test::addAfterEach(std::function<void (void)> teardown)
    {
        throw SyntaxException("a test case cannot contain afterEach()");
    }

    void Test::addSuite(Mode mode, string description,
        std::function<void (void)> suite)
    {
        throw SyntaxException("a test case cannot contain describe(), "
            "fdescribe(), xdescribe()");
    }

    void Test::addTest(Mode mode, string description,
        std::function<void (void)> test)
    {
        throw SyntaxException("a test case cannot contain it(), fit(), "
            "xit()");
    }

    Matcher Test::expect()
    {
        return Matcher();
    }

    void Test::evaluate()
    {
        if (expectCount == 0)
            cout << "WARNING: test case '" << description <<
                "' defines no expectations" << endl;
    }
}
