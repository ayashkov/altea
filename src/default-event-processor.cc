#include <iostream>

#include "default-event-processor.hh"

using namespace std;

namespace altea {
    void DefaultEventProcessor::process(const Event &event)
    {
        if (event.target == TEST || event.target == SUITE)
            processContainer(event);
        else if (event.target == EXPECTATION)
            log(event.message + " " + (string)event.location);
    }

    void DefaultEventProcessor::processContainer(const Event &event)
    {
        if (event.action == START) {
            log(event.message);
            ++level;
        } else if (event.action == STOP || event.action == FAIL ||
            event.action == ABORT)
            --level;
        else if (event.action == SKIP)
            log("SKIPPED: " + event.message);
    }

    void DefaultEventProcessor::log(const string &message)
    {
        for (int i = 0; i < level; i++)
            cout << "  ";

        cout << message << endl;
    }
}
