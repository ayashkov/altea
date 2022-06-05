#ifndef __TEST_HH
#define __TEST_HH

#include <string>
#include <functional>

#include "testable.hh"
#include "void-matcher.hh"
#include "bool-matcher.hh"

namespace altea {
    class Test: public Testable {
    public:
        Test(const Location &location, Context *const context,
            const Mode mode, const std::string &description,
            std::function<void (void)> test);

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

        virtual VoidMatcher doExpect(const Location &location);

        virtual BoolMatcher doExpect(const Location &location,
            const bool value);
    };
}

#endif // __TEST_HH
