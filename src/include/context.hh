#ifndef __CONTEXT_HH
#define __CONTEXT_HH

#include <string>
#include <functional>

#include "location.hh"
#include "testable.hh"
#include "suite.hh"
#include "event-processor.hh"
#include "void-matcher.hh"
#include "string-matcher.hh"
#include "bool-matcher.hh"
#include "long-matcher.hh"

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
            return eventProcessor == nullptr;
        }

        inline bool isFailed() const
        {
            return failed;
        }

        inline void markFailed()
        {
            failed = true;
        }

        inline void addBeforeAll(const std::string &file, const int line,
            std::function<void (void)> setup)
        {
            current->addBeforeAll(Location(file, line), setup);
        }

        inline void addBeforeEach(const std::string &file, const int line,
            std::function<void (void)> setup)
        {
            current->addBeforeEach(Location(file, line), setup);
        }

        inline void addAfterAll(const std::string &file, const int line,
            std::function<void (void)> teardown)
        {
            current->addAfterAll(Location(file, line), teardown);
        }

        inline void addAfterEach(const std::string &file, const int line,
            std::function<void (void)> teardown)
        {
            current->addAfterEach(Location(file, line), teardown);
        }

        inline int addSuite(const std::string &file, const int line,
            const Mode mode, const std::string &description,
            std::function<void (void)> suite)
        {
            current->addSuite(Location(file, line), mode, description,
                suite);

            return 0;
        }

        inline void addTest(const std::string &file, const int line,
            const Mode mode, const std::string &description,
            std::function<void (void)> test)
        {
            current->addTest(Location(file, line), mode, description, test);
        }

        inline VoidMatcher doExpect(const std::string &file,
            const int line)
        {
            return current->doExpect(Location(file, line));
        }

        inline StringMatcher doExpect(const std::string &file,
            const int line, const char *value)
        {
            return current->doExpect(Location(file, line),
                (std::string)value);
        }

        inline StringMatcher doExpect(const std::string &file,
            const int line, const std::string &value)
        {
            return current->doExpect(Location(file, line), value);
        }

        inline BoolMatcher doExpect(const std::string &file,
            const int line, const bool value)
        {
            return current->doExpect(Location(file, line), value);
        }

        inline LongMatcher doExpect(const std::string &file,
            const int line, const long value)
        {
            return current->doExpect(Location(file, line), value);
        }

        inline LongMatcher doExpect(const std::string &file,
            const int line, const int value)
        {
            return current->doExpect(Location(file, line), (long)value);
        }

        inline LongMatcher doExpect(const std::string &file,
            const int line, const short value)
        {
            return current->doExpect(Location(file, line), (long)value);
        }

        inline LongMatcher doExpect(const std::string &file,
            const int line, const char value)
        {
            return current->doExpect(Location(file, line), (long)value);
        }

        inline void process(const Event &event)
        {
            eventProcessor->process(event);
        }

        void run(EventProcessor *const ep);

    private:
        Suite root;

        Testable *current;

        EventProcessor *eventProcessor = nullptr;

        bool failed = false;
    };
}

#endif // __CONTEXT_HH
