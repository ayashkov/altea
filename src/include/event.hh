#ifndef __EVENT_HH
#define __EVENT_HH

#include <string>

#include "location.hh"

namespace altea {
    enum Target { SUITE, BEFORE_ALL, BEFORE_EACH, TEST, EXPECTATION,
        AFTER_EACH, AFTER_ALL };

    enum Action { SKIP, START, STOP, FAIL, ABORT };

    class Event {
    public:
        const Location location;

        const Target target;

        const Action action;

        const std::string message;

        Event(const Location &location, const Target target,
            const Action action, const std::string &message):
            location(location), target(target), action(action),
            message(message)
        {
        }
    };
}

#endif // __EVENT_HH
