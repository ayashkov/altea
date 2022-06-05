#include <algorithm>
#include <iostream>

#include "altea.hh"
#include "test-event-processor.hh"

using namespace altea;
using namespace std;

static auto _ = describe("Context", [] {
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

    it("should run to success when no suites", [&] {
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
    });

    it("should run lambdas twice in NORMAL suites", [&] {
        int one = 0;
        int two = 0;

        context->addSuite(__FILE__, __LINE__, NORMAL, "one", [&] {
            ++one;
        });
        context->addSuite(__FILE__, __LINE__, NORMAL, "two", [&] {
            ++two;
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(one == 2).toBeTrue();
        expect(two == 2).toBeTrue();
    });

    it("should run lambdas once in NORMAL tests in NORMAL suites", [&] {
        int oneOfOne = 0;
        int twoOfOne = 0;
        int oneOfTwo = 0;

        context->addSuite(__FILE__, __LINE__, NORMAL, "one", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "one of one", [&] {
                ++oneOfOne;
            });
            context->addTest(__FILE__, __LINE__, NORMAL, "two of one", [&] {
                ++twoOfOne;
            });
        });
        context->addSuite(__FILE__, __LINE__, NORMAL, "two", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "one of two", [&] {
                ++oneOfTwo;
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(oneOfOne == 1).toBeTrue();
        expect(twoOfOne == 1).toBeTrue();
        expect(oneOfTwo == 1).toBeTrue();
    });

    it("should run NORMAL tests in nested NORMAL suites", [&] {
        int nested = 0;

        context->addSuite(__FILE__, __LINE__, NORMAL, "grandfather", [&] {
            context->addSuite(__FILE__, __LINE__, NORMAL, "father", [&] {
                context->addSuite(__FILE__, __LINE__, NORMAL, "son", [&] {
                    context->addTest(__FILE__, __LINE__, NORMAL, "nested", [&] {
                        ++nested;
                    });
                });
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(nested == 1).toBeTrue();
    });
});
