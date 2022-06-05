#include "altea.hh"
#include "test-event-processor.hh"

using namespace altea;

static auto _ = describe("Expect", [] {
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

    it("should succeed when #isTrue() is called for true", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, true).toBeTrue();
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
    });

    it("should fail when #isTrue() is called for false", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, false).toBeTrue();
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });

    it("should succeed when #isFalse() is called for false", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, false).toBeFalse();
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
    });

    it("should fail when #isFalse() is called for true", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, true).toBeFalse();
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });

    it("should not abort the test on a failure", [&] {
        bool reached = false;

        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__).toFail("fail");
                context->doExpect(__FILE__, __LINE__, true).toBeFalse();
                context->doExpect(__FILE__, __LINE__, false).toBeTrue();

                reached = true;
            });
        });
        context->run(ep);

        expect(reached).toBeTrue();
    });
});
