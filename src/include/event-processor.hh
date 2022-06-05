#ifndef __EVENT_PROCESSOR_HH
#define __EVENT_PROCESSOR_HH

#include "event.hh"

namespace altea {
    class EventProcessor {
    public:
        virtual void process(const Event &event) = 0;

        inline bool isSuccessful()
        {
            return successful;
        }

    protected:
        bool successful = true;
    };
}

#endif // __EVENT_PROCESSOR_HH
