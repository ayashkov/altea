#ifndef __ALTEA_HH
#define __ALTEA_HH

#include <string>
#include <functional>
#include <queue>
#include <vector>

namespace altea {
    enum Mode { NORMAL, FOCUSED, EXCLUDED };

    class Testable {
    public:
        const std::string description;

        Testable(Mode mode, std::string description,
            std::function<void (void)> testable): mode(mode),
            description(description), testable(testable)
        {
        }

        virtual ~Testable()
        {
        }

        inline bool skipped(bool focusedMode)
        {
            return mode == EXCLUDED || (focusedMode && mode != FOCUSED);
        }

        virtual void test() = 0;
    protected:
        Mode mode;

        std::function<void (void)> testable;
    };

    class Test: public Testable {
    public:
        Test(Mode mode, std::string description,
            std::function<void (void)> test);

        virtual void test();
    };

    class Suite: public Testable {
    public:
        Suite(Mode mode, std::string description,
            std::function<void (void)> suite);

        virtual ~Suite();

        inline Suite *with(std::function<void (void)> suite)
        {
            testable = suite;

            return this;
        }

        void addBeforeAll(std::function<void (void)> setup);

        void addBeforeEach(std::function<void (void)> setup);

        void addAfterAll(std::function<void (void)> teardown);

        void addAfterEach(std::function<void (void)> teardown);

        void addSuite(Mode mode, std::string description,
            std::function<void (void)> suite);

        void addTest(Mode mode, std::string description,
            std::function<void (void)> test);

        virtual void test();

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

    class Context {
    public:
        Context();

        ~Context();

        inline Suite *getCurrent()
        {
            return current;
        }

        inline Suite *updateCurrent(Suite *next)
        {
            Suite *prev = current;

            current = next;

            return prev;
        }

        inline bool isDiscovery()
        {
            return discovery;
        }

        void run();

    private:
        Suite root;

        Suite *current;

        bool discovery = true;
    };

    extern Context context;

    inline void beforeAll(std::function<void (void)> setup)
    {
        context.getCurrent()->addBeforeAll(setup);
    }

    inline void beforeEach(std::function<void (void)> setup)
    {
        context.getCurrent()->addBeforeEach(setup);
    }

    inline void afterAll(std::function<void (void)> teardown)
    {
        context.getCurrent()->addAfterAll(teardown);
    }

    inline void afterEach(std::function<void (void)> teardown)
    {
        context.getCurrent()->addAfterEach(teardown);
    }

    inline int describe(std::string description,
        std::function<void (void)> suite)
    {
        context.getCurrent()->addSuite(NORMAL, description, suite);

        return 0;
    }

    inline int fdescribe(std::string description,
        std::function<void (void)> suite)
    {
        context.getCurrent()->addSuite(FOCUSED, description, suite);

        return 0;
    }

    inline int xdescribe(std::string description,
        std::function<void (void)> suite)
    {
        context.getCurrent()->addSuite(EXCLUDED, description, suite);

        return 0;
    }

    inline void it(std::string description,
        std::function<void (void)> test)
    {
        context.getCurrent()->addTest(NORMAL, description, test);
    }

    inline void fit(std::string description,
        std::function<void (void)> test)
    {
        context.getCurrent()->addTest(FOCUSED, description, test);
    }

    inline void xit(std::string description,
        std::function<void (void)> test)
    {
        context.getCurrent()->addTest(EXCLUDED, description, test);
    }
}

#endif // __ALTEA_HH
