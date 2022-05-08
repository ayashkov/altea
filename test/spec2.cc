#include <iostream>
#include "altea.hh"

using namespace std;
using namespace altea;

static auto _ = describe("Top-level 2", [] {
    it("should not run an unfocused test", [&] {
        cout << "DO NOT RUN" << endl;
    });

    it("should run when focused", [&] {
        cout << "under top level 2" << endl;
    });

    fdescribe("focused suite", [&] {
        it("should run under a focused suite", [&] {
            cout << "under sub level 2" << endl;
        });
    });
});
