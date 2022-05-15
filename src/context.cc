#include <iostream>
#include "altea.hh"

using namespace std;
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

    void Context::recordExpect()
    {
        current->recordExpect();
    }

    void Context::recordFailure(const string &file, int line,
        const string &message)
    {
        auto m = SourceMessage(file, line, "Failure", message);

        current->addFailure(m);
        failed = true;
    }

    void Context::log(const std::string &message)
    {
        cout << message << endl;
    }
}

int main()
{
    try {
        context.run();

        return context.isFailed() ? 1 : 0;
    } catch (const SyntaxException &ex) {
        cerr << ex.what() << endl;
    } catch (const exception &ex) {
        cerr << "Runtime error: " << ex.what() << endl;
    } catch (...) {
        cerr << "Caught unhandled exception" << endl;
    }

    return 2;
}
