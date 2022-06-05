#include <iostream>
#include <exception>

#include "context.hh"
#include "default-event-processor.hh"
#include "syntax-exception.hh"

using namespace std;
using namespace altea;

namespace altea {
    static DefaultEventProcessor eventProcessor;

    Context __context__(&eventProcessor);
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
