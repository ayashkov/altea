#include <climits>
#include <iostream>
#include "altea.hh"

using namespace std;

namespace altea {
    Suite::Suite(Mode mode, string description,
        std::function<void (void)> suite): Testable(mode, description,
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

    void Suite::addSuite(Mode mode, string description,
        std::function<void (void)> suite)
    {
        if (context.isDiscovery()) {
            auto sub = new Suite(mode, description, suite);
            auto prev = context.updateCurrent(sub);

            suite();
            context.updateCurrent(prev);
            subSuites.push(sub);
            adjustMode(sub->mode);
            ++discovered;
        } else {
            auto sub = subSuites.front()->with(suite);

            subSuites.pop();
            testables.push_back(sub);

            if (isLastCall())
                run();
        }
    }

    void Suite::addTest(Mode mode, string description,
        std::function<void (void)> test)
    {
        if (context.isDiscovery()) {
            adjustMode(mode);
            ++discovered;
        } else {
            testables.push_back(new Test(mode, description, test));

            if (isLastCall())
                run();
        }
    }

    Matcher Suite::expect()
    {
        throw SyntaxException("a suite cannot contain expect()");
    }

    void Suite::rootRun()
    {
        while (!subSuites.empty()) {
            auto sub = subSuites.front();

            subSuites.pop();
            runOne(sub);
        }
    }

    void Suite::adjustMode(Mode mode)
    {
        if (mode == FOCUSED) {
            focusedMode = true;
            this->mode = FOCUSED;
        }
    }

    void Suite::add(std::function<void(void)> mutator)
    {
        if (context.isDiscovery())
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

    void Suite::run()
    {
        for (auto setup : beforeAll)
            setup();

        for (auto testable : testables)
            runOne(testable);

        for (auto teardown : afterAll)
            teardown();
    }

    void Suite::runOne(Testable *testable)
    {
        if (testable->skipped(focusedMode))
            return;

        auto prev = context.updateCurrent(testable);

        cout << testable->description << endl;

        for (auto setup : beforeEach)
            setup();

        testable->test();

        for (auto teardown : afterEach)
            teardown();

        testable->evaluate();
        context.updateCurrent(prev);
    }
}
