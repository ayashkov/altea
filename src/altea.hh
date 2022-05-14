#ifndef __ALTEA_HH
#define __ALTEA_HH

#include <string>
#include <functional>
#include <queue>
#include <vector>
#include <exception>

namespace altea {
    enum Mode { NORMAL, FOCUSED, EXCLUDED };

    class TestException: public std::runtime_error {
    public:
        TestException(const char *what): std::runtime_error(what)
        {
        }
    };

    class SyntaxException: public TestException {
    public:
        SyntaxException(const char *what): TestException(what)
        {
        }
    };

    class Matcher {
    public:
        void nothing();
    };

    class Testable {
    public:
        const std::string description;

        Testable(Mode mode, std::string description,
            std::function<void (void)> testable);

        virtual ~Testable()
        {
        }

        bool skipped(bool focusedMode);

        void test();

        void recordExpect();

        virtual void addBeforeAll(std::function<void (void)> setup) = 0;

        virtual void addBeforeEach(std::function<void (void)> setup) = 0;

        virtual void addAfterAll(std::function<void (void)> teardown) = 0;

        virtual void addAfterEach(std::function<void (void)> teardown) = 0;

        virtual void addSuite(Mode mode, std::string description,
            std::function<void (void)> suite) = 0;

        virtual void addTest(Mode mode, std::string description,
            std::function<void (void)> test) = 0;

        virtual Matcher expect() = 0;

        virtual void evaluate();

    protected:
        Mode mode;

        std::function<void (void)> testable;

        int expectCount = 0;
    };

    class Test: public Testable {
    public:
        Test(Mode mode, std::string description,
            std::function<void (void)> test);

        virtual void addBeforeAll(std::function<void (void)> setup);

        virtual void addBeforeEach(std::function<void (void)> setup);

        virtual void addAfterAll(std::function<void (void)> teardown);

        virtual void addAfterEach(std::function<void (void)> teardown);

        virtual void addSuite(Mode mode, std::string description,
            std::function<void (void)> suite);

        virtual void addTest(Mode mode, std::string description,
            std::function<void (void)> test);

        virtual Matcher expect();

        virtual void evaluate();
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

        virtual void addBeforeAll(std::function<void (void)> setup);

        virtual void addBeforeEach(std::function<void (void)> setup);

        virtual void addAfterAll(std::function<void (void)> teardown);

        virtual void addAfterEach(std::function<void (void)> teardown);

        virtual void addSuite(Mode mode, std::string description,
            std::function<void (void)> suite);

        virtual void addTest(Mode mode, std::string description,
            std::function<void (void)> test);

        virtual Matcher expect();

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

        inline Testable *getCurrent()
        {
            return current;
        }

        inline Testable *updateCurrent(Testable *next)
        {
            auto prev = current;

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

        Testable *current;

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

    inline Matcher expect()
    {
        return context.getCurrent()->expect();
    }
}

#endif // __ALTEA_HH
