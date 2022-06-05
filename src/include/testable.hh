#ifndef __TESTABLE_HH
#define __TESTABLE_HH

#include <string>
#include <functional>
#include <vector>

#include "executable.hh"
#include "void-matcher.hh"
#include "bool-matcher.hh"
#include "source-message.hh"

namespace altea {
    enum Mode { NORMAL, FOCUSED, EXCLUDED };

    class Context;

    class Testable: public Executable {
    public:
        const std::string description;

        Testable(const Location &location, Context *const context,
            const Mode mode, const std::string &description,
            std::function<void (void)> testable);

        bool skipped(const bool focusedMode);

        void recordExpect();

        void recordFailure(const Location &location,
            const std::string &message);

        virtual void addBeforeAll(const Location &location,
            std::function<void (void)> setup) = 0;

        virtual void addBeforeEach(const Location &location,
            std::function<void (void)> setup) = 0;

        virtual void addAfterAll(const Location &location,
            std::function<void (void)> teardown) = 0;

        virtual void addAfterEach(const Location &location,
            std::function<void (void)> teardown) = 0;

        virtual void addSuite(const Location &location, const Mode mode,
            const std::string &description,
            std::function<void (void)> suite) = 0;

        virtual void addTest(const Location &location, const Mode mode,
            const std::string &description,
            std::function<void (void)> test) = 0;

        virtual VoidMatcher doExpect(const Location &location);

        virtual BoolMatcher doExpect(const Location &location,
            const bool value);

    protected:
        Mode mode;

        int expectCount = 0;
    };
}

#endif // __TESTABLE_HH
