#include "altea.hh"
#include "default-event-processor.hh"

using namespace altea;
using namespace std;

static DefaultEventProcessor ep;

static auto _ = describe("Context", [] {
    it("should do nothing when no suites", [] {
        Context context;

        context.run(&ep);

        expect().nothing();
    });

    it("should do nothing when it has empty NORMAL suites", [] {
        Context context;

        context.addSuite(__FILE__, __LINE__, NORMAL, "one", [] {});
        context.addSuite(__FILE__, __LINE__, NORMAL, "two", [] {});
        context.run(&ep);

        expect().nothing();
    });

    it("should run NORMAL tests when defined in NORMAL suites", [] {
        Context context;
        int testCount = 0;

        context.addSuite(__FILE__, __LINE__, NORMAL, "one", [&] {
            context.addTest(__FILE__, __LINE__, NORMAL, "one of one", [&] {
                ++testCount;

                context.doExpect(__FILE__, __LINE__).nothing();
            });
            context.addTest(__FILE__, __LINE__, NORMAL, "two of one", [&] {
                ++testCount;

                context.doExpect(__FILE__, __LINE__).nothing();
            });
        });
        context.addSuite(__FILE__, __LINE__, NORMAL, "two", [&] {
            context.addTest(__FILE__, __LINE__, NORMAL, "one of one", [&] {
                ++testCount;

                context.doExpect(__FILE__, __LINE__).nothing();
            });
        });
        context.run(&ep);

        expect(testCount == 3).toBeTrue();
    });
});
