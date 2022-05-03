#include <climits>
#include <iostream>
#include "altea.hh"

using namespace std;

namespace altea {
    Suite::Suite(): Testable("top", nullptr)
    {
        discovered = INT_MAX;
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
        for (auto s : beforeAll)
            s();

        for (auto t : testables) {
            cout << t->description << endl;
            t->test();
        }
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
        return beforeAll.size() + testables.size() >= discovered;
    }
}
