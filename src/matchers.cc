#include "altea.hh"

using namespace std;

namespace altea {
    void Matcher::nothing()
    {
        context.recordExpect();
    }

    void Matcher::fail(const std::string &message)
    {
        context.recordFailure(message);
    }
}
