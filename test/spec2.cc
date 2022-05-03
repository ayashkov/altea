#include <iostream>
#include "altea.hh"

using namespace std;
using namespace altea;

static auto _ = describe("Top-level 2", [] {
    it("should run a test", [&] {
        cout << "under top level 2" << endl;
    });
});
