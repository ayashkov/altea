#ifndef __VOID_MATCHER_HH
#define __VOID_MATCHER_HH

#include <string>

#include "base-matcher.hh"

namespace altea {
    class VoidMatcher: public BaseMatcher {
    public:
        VoidMatcher(const std::string &file, int line, Test *test);

        void nothing();

        void toFail(const std::string &description);
    };
}

#endif // __VOID_MATCHER_HH
