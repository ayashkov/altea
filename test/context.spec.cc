#include <string>

#include "altea.hh"
#include "test-event-processor.hh"

using namespace std;
using namespace altea;

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
        expect(one).toBe(2);
        expect(two).toBe(2);
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
        expect(oneOfOne).toBe(1);
        expect(twoOfOne).toBe(1);
        expect(oneOfTwo).toBe(1);
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
        expect(nested).toBe(1);
    });

    it("should run beforEach() in order before each test", [&] {
        string order;

        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addBeforeEach(__FILE__, __LINE__, [&] {
                order += "1";
            });

            context->addBeforeEach(__FILE__, __LINE__, [&] {
                order += "2";
            });

            context->addTest(__FILE__, __LINE__, NORMAL, "one", [&] {
                order += " ";
            });

            context->addTest(__FILE__, __LINE__, NORMAL, "two", [&] {
                order += " ";
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(order == "12 12 ").toBeTrue();
    });

    it("should run afterEach() in order after each test", [&] {
        string order;

        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addAfterEach(__FILE__, __LINE__, [&] {
                order += "1";
            });

            context->addAfterEach(__FILE__, __LINE__, [&] {
                order += "2";
            });

            context->addTest(__FILE__, __LINE__, NORMAL, "one", [&] {
                order += " ";
            });

            context->addTest(__FILE__, __LINE__, NORMAL, "two", [&] {
                order += " ";
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(order == " 12 12").toBeTrue();
    });

    it("should run beforEach() in order before each suite", [&] {
        string order;

        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addSuite(__FILE__, __LINE__, NORMAL, "one", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "child", [&] {
                    order += " ";
                });
            });

            context->addSuite(__FILE__, __LINE__, NORMAL, "two", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "child", [&] {
                    order += " ";
                });
            });

            context->addBeforeEach(__FILE__, __LINE__, [&] {
                order += "1";
            });

            context->addBeforeEach(__FILE__, __LINE__, [&] {
                order += "2";
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(order == "12 12 ").toBeTrue();
    });

    it("should run afterEach() in order after each suite", [&] {
        string order;

        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addSuite(__FILE__, __LINE__, NORMAL, "one", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "child", [&] {
                    order += " ";
                });
            });

            context->addSuite(__FILE__, __LINE__, NORMAL, "two", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "child", [&] {
                    order += " ";
                });
            });

            context->addAfterEach(__FILE__, __LINE__, [&] {
                order += "1";
            });

            context->addAfterEach(__FILE__, __LINE__, [&] {
                order += "2";
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(order == " 12 12").toBeTrue();
    });
});
