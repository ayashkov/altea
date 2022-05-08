#include "altea.hh"

using namespace altea;

namespace altea {
    Context context;

    Context::Context(): root(NORMAL, "root", nullptr)
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

int main()
{
    context.run();

    return 0;
}
