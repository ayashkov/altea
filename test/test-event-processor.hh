#ifndef __TEST_EVENT_PROCESSOR_HH
#define __TEST_EVENT_PROCESSOR_HH

#include "event-processor.hh"

namespace altea {
    class TestEventProcessor: public EventProcessor {
    public:
        virtual void process(const Event &event)
        {
        }
    };
}

#endif // __TEST_EVENT_PROCESSOR_HH
