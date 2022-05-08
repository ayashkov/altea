#include <iostream>
#include "altea.hh"

using namespace std;
using namespace altea;

static auto _ = describe("Top-level 2", [] {
    it("should not run an unfocused test", [&] {
        cout << "DO NOT RUN" << endl;
    });

    fit("should run a focused test", [&] {
        cout << "under top level 2" << endl;
    });
});
