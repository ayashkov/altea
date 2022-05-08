#include <climits>
#include <iostream>
#include "altea.hh"

using namespace std;

namespace altea {
    Suite::Suite(): Testable(false, "root", nullptr)
    {
        discovered = INT_MAX; // open-ended set of tests
    }

    Suite::Suite(bool focused, string description,
        std::function<void (void)> suite): Testable(focused, description,
        suite)
    {
    }

    Suite::~Suite()
    {
        for (auto test : testables)
            delete test;

        testables.clear();
    }

    void Suite::addBeforeAll(std::function<void (void)> setup)
    {
        add([=] {
            beforeAll.push_back(setup);
        });
    }

    void Suite::addBeforeEach(std::function<void (void)> setup)
    {
        add([=] {
            beforeEach.push_back(setup);
        });
    }

    void Suite::addAfterAll(std::function<void (void)> teardown)
    {
        add([=] {
            afterAll.push_back(teardown);
        });
    }

    void Suite::addAfterEach(std::function<void (void)> teardown)
    {
        add([=] {
            afterEach.push_back(teardown);
        });
    }

    int Suite::addSuite(string description, std::function<void (void)> suite)
    {
        add([=] {
            testables.push_back(new Suite(false, description, suite));
        });

        return 0;
    }

    void Suite::addTest(bool focused, string description,
        std::function<void (void)> test)
    {
        if (focused)
            focusedMode = true;

        add([=] {
            testables.push_back(new Test(focused, description, test));
        });
    }

    void Suite::test()
    {
        Suite *prev = context.updateCurrent(this);

        discovery = true;
        function();
        discovery = false;
        function();
        context.updateCurrent(prev);
    }

    void Suite::run()
    {
        for (auto setup : beforeAll)
            setup();

        for (auto testable : testables)
            runOne(testable);

        for (auto teardown : afterAll)
            teardown();
    }

    void Suite::add(std::function<void(void)> mutator)
    {
        if (discovery)
            ++discovered;
        else {
            mutator();

            if (isLastCall())
                run();
        }
    }

    bool Suite::isLastCall()
    {
        return beforeAll.size() + beforeEach.size() + afterAll.size() +
            afterEach.size() + testables.size() >= discovered;
    }

    void Suite::runOne(Testable *testable)
    {
        if (!testable->function || (focusedMode && !testable->focused))
            return;

        cout << testable->description << endl;

        for (auto setup : beforeEach)
            setup();

        testable->test();

        for (auto teardown : afterEach)
            teardown();
    }
}
