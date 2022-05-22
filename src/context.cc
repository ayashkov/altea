#include <iostream>
#include "altea.hh"

using namespace std;
using namespace altea;

namespace altea {
    Context __context__;

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

int main(int argc, char *argv[])
{
    try {
        __context__.run();

        return __context__.isFailed() ? 1 : 0;
    } catch (const SyntaxException &ex) {
        cerr << ex.what() << endl;
    } catch (const exception &ex) {
        cerr << "Runtime error: " << ex.what() << endl;
    } catch (...) {
        cerr << "Caught unhandled exception" << endl;
    }

    return 2;
}
