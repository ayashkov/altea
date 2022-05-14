#include "altea.hh"

using namespace std;

namespace altea {
    void Matcher::nothing()
    {
        context.getCurrent()->recordExpect();
    }
}
