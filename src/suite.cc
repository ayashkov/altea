#include <exception>

#include "suite.hh"
#include "test.hh"
#include "context.hh"

using namespace std;

namespace altea {
    Suite::Suite(const Location &location, Context *const context,
        const Mode mode, const string &description,
        function<void (void)> suite):
        Testable(location, context, mode, description, suite)
    {
    }

    Suite::~Suite()
    {
        for (auto test : testables)
            delete test;

        testables.clear();
    }

    void Suite::addBeforeAll(const Location &location,
        function<void (void)> setup)
    {
        add([=] {
            beforeAll.push_back(Executable(location, context, setup));
        });
    }

    void Suite::addBeforeEach(const Location &location,
        function<void (void)> setup)
    {
        add([=] {
            beforeEach.push_back(Executable(location, context, setup));
        });
    }

    void Suite::addAfterAll(const Location &location,
        function<void (void)> teardown)
    {
        add([=] {
            afterAll.push_back(Executable(location, context, teardown));
        });
    }

    void Suite::addAfterEach(const Location &location,
        function<void (void)> teardown)
    {
        add([=] {
            afterEach.push_back(Executable(location, context, teardown));
        });
    }

    void Suite::addSuite(const Location &location, const Mode mode,
        const string &description, function<void (void)> suite)
    {
        if (context->isDiscovery()) {
            auto sub = new Suite(location, context, mode, description,
                suite);
            auto prev = context->updateCurrent(sub);

            suite();
            context->updateCurrent(prev);
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

    void Suite::addTest(const Location &location, const Mode mode,
        const string &description, function<void (void)> test)
    {
        if (context->isDiscovery()) {
            adjustMode(mode);
            ++discovered;
        } else {
            testables.push_back(new Test(location, context, mode,
                description, test));

            if (isLastCall())
                run();
        }
    }

    void Suite::rootRun()
    {
        while (!subSuites.empty()) {
            auto sub = subSuites.front();

            subSuites.pop();
            runTestable(sub);
        }
    }

    void Suite::adjustMode(const Mode mode)
    {
        if (mode == FOCUSED) {
            focusedMode = true;
            this->mode = FOCUSED;
        }
    }

    void Suite::add(function<void(void)> mutator)
    {
        if (context->isDiscovery())
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
        for (auto testable : testables)
            runTestable(testable);

        if (beforeAllDone)
            for (auto teardown : afterAll)
                runExecutable(&teardown, AFTER_ALL, "");

        beforeAllDone = false;
    }

    void Suite::runTestable(Testable *const testable)
    {
        if (testable->skipped(focusedMode)) {
            context->process(Event(testable->location, TEST, SKIP,
                testable->description));

            return;
        }

        if (!beforeAllDone) {
            for (auto setup : beforeAll)
                runExecutable(&setup, BEFORE_ALL, "");

            beforeAllDone = true;
        }

        auto prev = context->updateCurrent(testable);

        for (auto setup : beforeEach)
            runExecutable(&setup, BEFORE_EACH, "");

        runExecutable(testable, TEST, testable->description);

        for (auto teardown : afterEach)
            runExecutable(&teardown, AFTER_EACH, "");

        context->updateCurrent(prev);
    }

    void Suite::runExecutable(Executable *const executable,
        const Target target, const string &description)
    {
        try {
            context->process(Event(executable->location, target, START,
                description));
            executable->execute();
            context->process(Event(executable->location, target, STOP,
                description));
        } catch (const exception &ex) {
            context->process(Event(executable->location, target, ABORT,
                ex.what()));

            throw ex;
        }
    }
}
