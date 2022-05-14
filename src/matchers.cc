#include "altea.hh"

using namespace std;

namespace altea {
    Matcher::Matcher(const string &file, int line): file(file), line(line)
    {
    }

    void Matcher::nothing()
    {
        context.recordExpect();
    }

    void Matcher::toFail(const std::string &message)
    {
        context.recordExpect();
        context.recordFailure(file, line, message);
    }
}
