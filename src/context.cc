#include <iostream>

#include "context.hh"
#include "syntax-exception.hh"

using namespace std;
using namespace altea;

namespace altea {
    Context::Context(): root(".", 0, this, NORMAL, "root", nullptr)
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

    void Context::log(const std::string &message)
    {
        cout << message << endl;
    }
}
