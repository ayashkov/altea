#ifndef __ALTEA_HH
#define __ALTEA_HH

#include <string>
#include <functional>
#include <vector>

namespace altea {
    class Testable {
    public:
        const std::string description;

        const std::function<void (void)> function;

        Testable(std::string d, std::function<void (void)> f):
            description(d), function(f)
        {
        }

        virtual ~Testable()
        {
        }

        virtual void test() = 0;
    };

    class Test: public Testable {
    public:
        Test(std::string d, std::function<void (void)> t);

        void test();
    };

    class Suite: public Testable {
    public:
        Suite();

        Suite(std::string d, std::function<void (void)> s);

        virtual ~Suite();

        int addSuite(std::string description,
            std::function<void (void)> suite);

        void addTest(std::string description,
            std::function<void (void)> test);

        void test();

        void run();

    private:
        bool discovery = false;

        int discovered = 0;

        std::vector<Testable*> testables;

        void add(std::function<Testable* (void)> gen);

        void checkAndRun();
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

    inline int describe(std::string description,
        std::function<void (void)> suite)
    {
        return context.getCurrent()->addSuite(description, suite);
    }

    inline void it(std::string description,
        std::function<void (void)> test)
    {
        context.getCurrent()->addTest(description, test);
    }

    inline int xdescribe(std::string description,
        std::function<void (void)> suite)
    {
        return context.getCurrent()->addSuite(description, nullptr);
    }

    inline void xit(std::string description,
        std::function<void (void)> test)
    {
        context.getCurrent()->addTest(description, nullptr);
    }
}

#endif // __ALTEA_HH
