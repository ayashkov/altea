#include "altea.hh"

using namespace altea;

static auto _ = describe("Top-level 2", [] {
    it("should not run an unfocused test", [&] {
        expect().nothing();
    });

    it("should run when focused", [&] {
        expect().nothing();
    });

    describe("focused suite", [&] {
        it("should run under a focused suite", [&] {
            expect().nothing();
        });
    });
});
