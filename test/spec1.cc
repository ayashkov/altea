#include <iostream>
#include <string>
#include "altea.hh"

using namespace std;
using namespace altea;

static auto _ = describe("Top-level 1", [] {
    string var = "";

    beforeAll([&] {
        var = "before all";
    });

    afterAll([&] {
        var = "";
    });

    beforeEach([&] {
        var += "/";
    });

    afterEach([&] {
        var += "\\";
    });

    it("should run one test", [&] {
        expect().nothing();
    });

    it("should run more than one test", [&] {
        expect().nothing();
    });

    it("should have access to variables", [&] {
        cout << var << endl;

        expect().nothing();
    });

    xit("should nor execute disabled tests", [&] {
        expect().nothing();
    });

    describe("Sub context", [&] {
        auto sub = "sub variable";

        it("should run tests in subcontext", [&] {
            expect().nothing();
        });

        it("should still have access to variables", [&] {
            cout << var << endl;
            cout << sub << endl;

            expect().nothing();
        });
    });

    xdescribe("Disabled context", [&] {
        it("should not run tests in disabled context", [&] {
            expect().nothing();
        });
    });
});
