#include <iostream>

#include "default-event-processor.hh"

using namespace std;

namespace altea {
    void DefaultEventProcessor::process(const Event &event)
    {
        switch (event.action) {
        case START:
            if (event.target == SUITE || event.target == TEST)
                log(event.message);

            ++level;

            break;
        case FAIL:
        case ABORT:
            if (event.target == TEST)
                successful = false;
            else if (event.target == EXPECTATION)
                log(event.message + " " + (string)event.location);
        case STOP:
            --level;

            break;
        }
    }

    void DefaultEventProcessor::log(const string &message)
    {
        for (int i = 0; i < level; i++)
            cout << "  ";

        cout << message << endl;
    }
}
