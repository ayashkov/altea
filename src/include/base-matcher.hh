#ifndef __BASE_MATCHER_HH
#define __BASE_MATCHER_HH

#include <string>

#include "location.hh"

namespace altea {
    class Test;

    class BaseMatcher {
    public:
        BaseMatcher(const Location &location, Test *const test);

    protected:
        const Location location;

        Test *const test;
    };
}

#endif // __BASE_MATCHER_HH
