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
        expect(2 * 2 == 4).toBeTrue();
    });

    it("should run more than one test", [&] {
        expect(1 == 2).toBeFalse();
    });

    it("should have access to variables", [&] {
        cout << var << endl;

        expect().nothing();
    });

    xit("should nor execute disabled tests", [&] {
        fail("must not run");
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
            expect().toFail("must not run");
        });
    });
});
