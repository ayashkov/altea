#ifndef __SUITE_HH
#define __SUITE_HH

#include <string>
#include <functional>
#include <queue>
#include <vector>

#include "event.hh"
#include "testable.hh"

namespace altea {
    class Suite: public Testable {
    public:
        Suite(const Location &location, Context *const context,
            const Mode mode, const std::string &description,
            std::function<void (void)> suite);

        virtual ~Suite();

        inline Suite *with(std::function<void (void)> suite)
        {
            executable = suite;

            return this;
        }

        virtual void addBeforeAll(const Location &location,
            std::function<void (void)> setup);

        virtual void addBeforeEach(const Location &location,
            std::function<void (void)> setup);

        virtual void addAfterAll(const Location &location,
            std::function<void (void)> teardown);

        virtual void addAfterEach(const Location &location,
            std::function<void (void)> teardown);

        virtual void addSuite(const Location &location, const Mode mode,
            const std::string &description,
            std::function<void (void)> suite);

        virtual void addTest(const Location &location, const Mode mode,
            const std::string &description,
            std::function<void (void)> test);

        void rootRun();

    private:
        bool focusedMode = false;

        bool beforeAllDone = false;

        int discovered = 0;

        std::queue<Suite*> subSuites;

        std::vector<Executable> beforeAll;

        std::vector<Executable> beforeEach;

        std::vector<Executable> afterAll;

        std::vector<Executable> afterEach;

        std::vector<Testable*> testables;

        void adjustMode(const Mode mode);

        void add(std::function<void(void)> mutator);

        bool isLastCall();

        void run();

        void runTestable(Testable *const testable);

        void runExecutable(Executable *const executable,
            const Target target, const std::string &description);
    };
}

#endif // __SUITE_HH
