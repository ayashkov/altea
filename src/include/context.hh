#ifndef __CONTEXT_HH
#define __CONTEXT_HH

#include <string>
#include <functional>

#include "location.hh"
#include "testable.hh"
#include "suite.hh"
#include "event-processor.hh"

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

        inline void addSuite(const std::string &file, const int line,
            const Mode mode, const std::string &description,
            std::function<void (void)> suite)
        {
            current->addSuite(Location(file, line), mode, description,
                suite);
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

        inline BoolMatcher doExpect(const std::string &file,
            const int line, const bool value)
        {
            return current->doExpect(Location(file, line), value);
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
