#include "executable.hh"

using namespace std;

namespace altea {
    Executable::Executable(const Location &location,
        Context *const context, function<void (void)> executable):
        location(location), context(context), executable(executable)
    {
    }

    Executable::~Executable()
    {
    }

    void Executable::execute()
    {
        executable();
    }
}
