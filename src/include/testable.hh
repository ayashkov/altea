#ifndef __TESTABLE_HH
#define __TESTABLE_HH

#include <string>
#include <functional>
#include <vector>

#include "void-matcher.hh"
#include "bool-matcher.hh"
#include "source-message.hh"

namespace altea {
    enum Mode { NORMAL, FOCUSED, EXCLUDED };

    class Context;

    class Testable {
    public:
        const std::string file;

        const int line;

        const std::string description;

        Testable(const std::string &file, int line, Context *context,
            Mode mode, const std::string &description,
            std::function<void (void)> testable);

        virtual ~Testable()
        {
        }

        bool skipped(bool focusedMode);

        void test();

        void recordExpect();

        void recordFailure(const std::string &file, int line,
            const std::string &message);

        virtual void addBeforeAll(const std::string &file, int line,
            std::function<void (void)> setup) = 0;

        virtual void addBeforeEach(const std::string &file, int line,
            std::function<void (void)> setup) = 0;

        virtual void addAfterAll(const std::string &file, int line,
            std::function<void (void)> teardown) = 0;

        virtual void addAfterEach(const std::string &file, int line,
            std::function<void (void)> teardown) = 0;

        virtual void addSuite(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> suite) = 0;

        virtual void addTest(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> test) = 0;

        virtual VoidMatcher doExpect(const std::string &file, int line);

        virtual BoolMatcher doExpect(const std::string &file, int line,
            bool value);

        virtual void evaluate() const;

    protected:
        Context *const context;

        Mode mode;

        std::function<void (void)> testable;

        int expectCount = 0;

        std::vector<SourceMessage> failures;
    };
}

#endif // __TESTABLE_HH
