#include "altea.hh"
#include "test-event-processor.hh"

using namespace altea;

static auto _ = describe("Expect with integral type argument", [] {
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

    it("should succeed when #toBe(N) is called for the same number N", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, 42L).toBe(42);
                context->doExpect(__FILE__, __LINE__, -42).toBe(-42);
                context->doExpect(__FILE__, __LINE__, (short)42).toBe(42);
                context->doExpect(__FILE__, __LINE__, (char)42).toBe(42);
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
    });

    it("should fail when #toBe(N) is called for a different long N", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, 42L).toBe(43);
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });

    it("should fail when #toBe(N) is called for a different int N", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, 42).toBe(43);
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });

    it("should fail when #toBe(N) is called for a different short N", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, (short)42).toBe(43);
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });

    it("should fail when #toBe(N) is called for a different char N", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, (char)42).toBe(43);
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });

    it("should succeed when #toBeTruthy() is called for not 0", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, 12).toBeTruthy();
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
    });

    it("should fail when #toBeTruthy() is called for 0", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, 0).toBeTruthy();
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });

    it("should succeed when #toBeFalsy() is called for 0", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, 0).toBeFalsy();
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
    });

    it("should fail when #toBeFalsy() is called for not 0", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, 3).toBeFalsy();
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });

    it("should succeed when #NOT() negates the false outcome", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, 1).NOT().toBe(0);
                context->doExpect(__FILE__, __LINE__, 0).NOT().toBeTruthy();
                context->doExpect(__FILE__, __LINE__, 12).NOT().toBeFalsy();
                context->doExpect(__FILE__, __LINE__, 1).NOT().NOT().toBe(1);
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
    });

    it("should fail when #NOT() negates the true outcome", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                context->doExpect(__FILE__, __LINE__, 1).NOT().toBe(1);
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeTrue();
    });
});
