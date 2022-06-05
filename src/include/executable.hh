#ifndef __EXECUTABLE_HH
#define __EXECUTABLE_HH

#include <string>
#include <functional>

#include "location.hh"

namespace altea {
    class Context;

    class Executable {
    public:
        const Location location;

        Executable(const Location &location, Context *const context,
            std::function<void (void)> executable);

        virtual ~Executable();

        void execute();

    protected:
        Context *const context;

        std::function<void (void)> executable;
    };
}

#endif // __EXECUTABLE_HH
