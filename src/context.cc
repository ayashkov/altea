#include "context.hh"

using namespace altea;

namespace altea {
    Context::Context(EventProcessor *eventProcessor):
        root(Location(".", 0), this, NORMAL, "root", nullptr),
        eventProcessor(eventProcessor)
    {
        current = &root;
    }

    Context::~Context()
    {
    }

    void Context::run()
    {
        discovery = false;
        root.rootRun();
    }
}
