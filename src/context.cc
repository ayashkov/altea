#include "context.hh"

using namespace altea;

namespace altea {
    Context::Context():
        root(Location(".", 0), this, NORMAL, "root", nullptr)
    {
        current = &root;
    }

    Context::~Context()
    {
    }

    void Context::run(EventProcessor *const ep)
    {
        eventProcessor = ep;
        root.rootRun();
    }
}
