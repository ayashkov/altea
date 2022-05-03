#include "altea.hh"

using namespace altea;

namespace altea {
    Context context;

    Context::Context(): top()
    {
        current = &top;
    }

    Context::~Context()
    {
    }
}

int main()
{
    context.getCurrent()->run();

    return 0;
}
