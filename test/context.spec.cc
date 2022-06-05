#include "altea.hh"
#include "default-event-processor.hh"

using namespace altea;
using namespace std;

static auto _ = describe("Context", [] {
    DefaultEventProcessor *ep;
    Context *context;

    beforeEach([&] {
        ep = new DefaultEventProcessor();
        context = new Context();
    });

    afterEach([&] {
        delete context;
        context = nullptr;
        delete ep;
        ep = nullptr;
    });

    it("should do nothing when no suites", [&] {
        context->run(ep);

        expect().nothing();
    });

    it("should do nothing when it has empty NORMAL suites", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "one", [] {});
        context->addSuite(__FILE__, __LINE__, NORMAL, "two", [] {});
        context->run(ep);

        expect().nothing();
    });

    it("should run NORMAL tests when defined in NORMAL suites", [&] {
        int testCount = 0;

        context->addSuite(__FILE__, __LINE__, NORMAL, "one", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "one of one", [&] {
                ++testCount;

                context->doExpect(__FILE__, __LINE__).nothing();
            });
            context->addTest(__FILE__, __LINE__, NORMAL, "two of one", [&] {
                ++testCount;

                context->doExpect(__FILE__, __LINE__).nothing();
            });
        });
        context->addSuite(__FILE__, __LINE__, NORMAL, "two", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "one of one", [&] {
                ++testCount;

                context->doExpect(__FILE__, __LINE__).nothing();
            });
        });
        context->run(ep);

        expect(testCount == 3).toBeTrue();
    });
});
