#ifndef __DEFAULT_EVENT_PROCESSOR_HH
#define __DEFAULT_EVENT_PROCESSOR_HH

#include <string>

#include "event-processor.hh"

namespace altea {
    class DefaultEventProcessor: public EventProcessor {
    public:
        virtual void process(const Event &event);
    private:
        int level = 0;

        void processContainer(const Event &event);

        void log(const std::string &message);
    };
}

#endif // __DEFAULT_EVENT_PROCESSOR_HH
