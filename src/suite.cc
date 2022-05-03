#include <climits>
#include <iostream>
#include "altea.hh"

using namespace std;

namespace altea {
    Suite::Suite(): Testable("top", nullptr)
    {
        discovered = INT_MAX; // open-ended
    }

    Suite::Suite(string d, std::function<void (void)> s): Testable(d, s)
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

    int Suite::addSuite(string description, std::function<void (void)> suite)
    {
        add([=] {
            testables.push_back(new Suite(description, suite));
        });

        return 0;
    }

    void Suite::addTest(string description, std::function<void (void)> test)
    {
        add([=] {
            testables.push_back(new Test(description, test));
        });
    }

    void Suite::test()
    {
        if (!function)
            return;

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

        for (auto testable : testables) {
            cout << testable->description << endl;

            for (auto setup : beforeEach)
                setup();

            testable->test();
        }

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
            testables.size() >= discovered;
    }
}
