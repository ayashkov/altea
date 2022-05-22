#ifndef __SUITE_HH
#define __SUITE_HH

#include <string>
#include <functional>
#include <queue>
#include <vector>

#include "testable.hh"

namespace altea {
    class Suite: public Testable {
    public:
        Suite(const std::string &file, int line, Context *context,
            Mode mode, const std::string &description,
            std::function<void (void)> suite);

        virtual ~Suite();

        inline Suite *with(std::function<void (void)> suite)
        {
            testable = suite;

            return this;
        }

        virtual void addBeforeAll(const std::string &file, int line,
            std::function<void (void)> setup);

        virtual void addBeforeEach(const std::string &file, int line,
            std::function<void (void)> setup);

        virtual void addAfterAll(const std::string &file, int line,
            std::function<void (void)> teardown);

        virtual void addAfterEach(const std::string &file, int line,
            std::function<void (void)> teardown);

        virtual void addSuite(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> suite);

        virtual void addTest(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> test);

        void rootRun();

    private:
        bool focusedMode = false;

        int discovered = 0;

        std::queue<Suite*> subSuites;

        std::vector<std::function<void (void)>> beforeAll;

        std::vector<std::function<void (void)>> beforeEach;

        std::vector<std::function<void (void)>> afterAll;

        std::vector<std::function<void (void)>> afterEach;

        std::vector<Testable*> testables;

        void adjustMode(Mode mode);

        void add(std::function<void(void)> mutator);

        bool isLastCall();

        void run();

        void runOne(Testable *testable);
    };
}

#endif // __SUITE_HH
