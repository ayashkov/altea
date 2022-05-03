#include <iostream>
#include <string>
#include "altea.hh"

using namespace std;
using namespace altea;

static auto _ = describe("Top-level 1", [] {
    string var = "";

    beforeAll([&] {
        var = "before all";

        cout << "Before All" << endl;
    });

    afterAll([&] {
        var = "";

        cout << "After All" << endl;
    });

    it("should run one test", [&] {
        cout << "one" << endl;
    });

    it("should run more than one test", [&] {
        cout << "two" << endl;
    });

    it("should have access to variables", [&] {
        cout << var << endl;
    });

    xit("should nor execute disabled tests", [&] {
        cout << "DO NOT RUN" << endl;
    });

    describe("Sub context", [&] {
        auto sub = "sub variable";

        it("should run tests in subcontext", [&] {
            cout << "sub" << endl;
        });

        it("should still have access to variables", [&] {
            cout << var << endl;
            cout << sub << endl;
        });
    });

    xdescribe("Disabled context", [&] {
        it("should not run tests in disabled context", [&] {
            cout << "DO NOT RUN" << endl;
        });
    });
});
