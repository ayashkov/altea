#include "altea.hh"

using namespace std;

namespace altea {
    Matcher::Matcher(const string &file, int line): file(file), line(line)
    {
    }

    void Matcher::nothing()
    {
        __context__.recordExpect();
    }

    void Matcher::toFail(const std::string &message)
    {
        __context__.recordExpect();
        __context__.recordFailure(file, line, message);
    }
}
