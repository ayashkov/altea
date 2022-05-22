#ifndef __BASE_MATCHER_HH
#define __BASE_MATCHER_HH

#include <string>

namespace altea {
    class Test;

    class BaseMatcher {
    public:
        BaseMatcher(const std::string &file, int line, Test *test);

    protected:
        const std::string file;

        const int line;

        Test *const test;
    };
}

#endif // __BASE_MATCHER_HH
