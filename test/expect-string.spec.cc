#include "altea.hh"
#include "test-event-processor.hh"

using namespace altea;

static auto _ = describe("Expect with string argument", [] {
    TestEventProcessor *ep;
    Context *context;

    beforeEach([&] {
        ep = new TestEventProcessor();
        context = new Context();
    });

    afterEach([&] {
        delete context;
        delete ep;
    });

    it("should succeed when #toBe(S) is called for the same string S", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, "something")
                    .toBe("something");
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
    });

    it("should fail when #toBe(S) is called for a different string S", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, "something")
                    .toBe("different");
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });

    // it("should succeed when #NOT() negates the false outcome", [&] {
    //     context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
    //         context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
    //             context->doExpect(__FILE__, __LINE__, 1).NOT().toBe(0);
    //             context->doExpect(__FILE__, __LINE__, 0).NOT().toBeTruthy();
    //             context->doExpect(__FILE__, __LINE__, 12).NOT().toBeFalsy();
    //             context->doExpect(__FILE__, __LINE__, 1).NOT().NOT().toBe(1);
    //         });
    //     });
    //     context->run(ep);

    //     expect(context->isFailed()).toBeFalse();
    // });

    // it("should fail when #NOT() negates the true outcome", [&] {
    //     context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
    //         context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
    //             context->doExpect(__FILE__, __LINE__, 1).NOT().toBe(1);
    //         });
    //     });
    //     context->run(ep);

    //     expect(context->isFailed()).toBeTrue();
    // });
});
