#ifndef __ALTEA_HH
#define __ALTEA_HH

#include <string>
#include <functional>
#include <vector>

namespace altea {
    class Testable {
    public:
        const bool focused;

        const std::string description;

        const std::function<void (void)> function;

        Testable(bool focused, std::string description,
            std::function<void (void)> function): focused(focused),
            description(description), function(function)
        {
        }

        virtual ~Testable()
        {
        }

        virtual void test() = 0;
    };

    class Test: public Testable {
    public:
        Test(bool focused, std::string description,
            std::function<void (void)> test);

        void test();
    };

    class Suite: public Testable {
    public:
        Suite();

        Suite(bool focused, std::string description,
            std::function<void (void)> suite);

        virtual ~Suite();

        void addBeforeAll(std::function<void (void)> setup);

        void addBeforeEach(std::function<void (void)> setup);

        void addAfterAll(std::function<void (void)> teardown);

        void addAfterEach(std::function<void (void)> teardown);

        int addSuite(std::string description,
            std::function<void (void)> suite);

        void addTest(bool focused, std::string description,
            std::function<void (void)> test);

        void test();

        void run();

    private:
        bool focusedMode = false;

        bool discovery = false;

        int discovered = 0;

        std::vector<std::function<void (void)>> beforeAll;

        std::vector<std::function<void (void)>> beforeEach;

        std::vector<std::function<void (void)>> afterAll;

        std::vector<std::function<void (void)>> afterEach;

        std::vector<Testable*> testables;

        void add(std::function<void(void)> mutator);

        bool isLastCall();

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

    private:
        Suite top;

        Suite *current;
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
        return context.getCurrent()->addSuite(description, suite);
    }

    inline int xdescribe(std::string description,
        std::function<void (void)> suite)
    {
        return context.getCurrent()->addSuite(description, nullptr);
    }

    inline void it(std::string description,
        std::function<void (void)> test)
    {
        context.getCurrent()->addTest(false, description, test);
    }

    inline void fit(std::string description,
        std::function<void (void)> test)
    {
        context.getCurrent()->addTest(true, description, test);
    }

    inline void xit(std::string description,
        std::function<void (void)> test)
    {
        context.getCurrent()->addTest(false, description, nullptr);
    }
}

#endif // __ALTEA_HH
