#include "altea.hh"
#include "test-event-processor.hh"

using namespace altea;

static auto _ = describe("Expect with no arguments", [] {
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

    it("should succeed when #nothing() is called", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__).nothing();
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
    });

    it("should fail when #toFail() is called", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__).toFail("bang!");
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });
});
