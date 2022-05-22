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
        Test(const std::string &file, int line, Context *context,
            Mode mode, const std::string &description,
            std::function<void (void)> test);

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

        virtual VoidMatcher doExpect(const std::string &file, int line);

        virtual BoolMatcher doExpect(const std::string &file, int line,
            bool value);

        virtual void evaluate() const;
    };
}

#endif // __TEST_HH
