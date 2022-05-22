#ifndef __CONTEXT_HH
#define __CONTEXT_HH

#include <string>
#include <functional>

#include "testable.hh"
#include "suite.hh"

namespace altea {
    class Context {
    public:
        Context();

        ~Context();

        inline Testable *updateCurrent(Testable *next)
        {
            auto prev = current;

            current = next;

            return prev;
        }

        inline bool isDiscovery() const
        {
            return discovery;
        }

        inline bool isFailed() const
        {
            return failed;
        }

        inline void markFailed()
        {
            failed = true;
        }

        inline void addBeforeAll(const std::string &file, int line,
            std::function<void (void)> setup)
        {
            current->addBeforeAll(file, line, setup);
        }

        inline void addBeforeEach(const std::string &file, int line,
            std::function<void (void)> setup)
        {
            current->addBeforeEach(file, line, setup);
        }

        inline void addAfterAll(const std::string &file, int line,
            std::function<void (void)> teardown)
        {
            current->addAfterAll(file, line, teardown);
        }

        inline void addAfterEach(const std::string &file, int line,
            std::function<void (void)> teardown)
        {
            current->addAfterEach(file, line, teardown);
        }

        inline void addSuite(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> suite)
        {
            current->addSuite(file, line, mode, description, suite);
        }

        inline void addTest(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> test)
        {
            current->addTest(file, line, mode, description, test);
        }

        inline VoidMatcher doExpect(const std::string &file, int line)
        {
            return current->doExpect(file, line);
        }

        inline BoolMatcher doExpect(const std::string &file, int line,
            bool value)
        {
            return current->doExpect(file, line, value);
        }

        void run();

        void log(const std::string &message);

    private:
        Suite root;

        Testable *current;

        bool discovery = true;

        bool failed = false;
    };
}

#endif // __CONTEXT_HH
