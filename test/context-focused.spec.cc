#include <string>

#include "altea.hh"
#include "test-event-processor.hh"

using namespace std;
using namespace altea;

static auto _ = describe("Context focused execution", [] {
    TestEventProcessor *ep;
    Context *context;
    int focused;
    int normal;

    beforeEach([&] {
        ep = new TestEventProcessor();
        context = new Context();
        focused = 0;
        normal = 0;
    });

    afterEach([&] {
        delete context;
        delete ep;
    });

    it("should run only focused tests in a normal suite when present", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "normal", [&] {
                ++normal;
            });
            context->addTest(__FILE__, __LINE__, FOCUSED, "focused 1", [&] {
                ++focused;
            });
            context->addTest(__FILE__, __LINE__, FOCUSED, "focused 2", [&] {
                ++focused;
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(focused).toBe(2);
        expect(normal).toBe(0);
    });

    it("should run only focused tests in a focused suite when present", [&] {
        context->addSuite(__FILE__, __LINE__, FOCUSED, "suite", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "normal", [&] {
                ++normal;
            });
            context->addTest(__FILE__, __LINE__, FOCUSED, "focused 1", [&] {
                ++focused;
            });
            context->addTest(__FILE__, __LINE__, FOCUSED, "focused 2", [&] {
                ++focused;
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(focused).toBe(2);
        expect(normal).toBe(0);
    });

    it("should run all tests in a focused suite when no focused content", [&] {
        context->addSuite(__FILE__, __LINE__, FOCUSED, "focused", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "one", [&] {
                ++focused;
            });
            context->addTest(__FILE__, __LINE__, NORMAL, "two", [&] {
                ++focused;
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(focused).toBe(2);
    });

    it("should run only focused suites in a normal suite when present", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite", [&] {
            context->addSuite(__FILE__, __LINE__, NORMAL, "normal", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                    ++normal;
                });
            });
            context->addSuite(__FILE__, __LINE__, FOCUSED, "focused 1", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                    ++focused;
                });
            });
            context->addSuite(__FILE__, __LINE__, FOCUSED, "focused 2", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                    ++focused;
                });
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(focused).toBe(2);
        expect(normal).toBe(0);
    });

    it("should run only focused suites in a focused suite when present", [&] {
        context->addSuite(__FILE__, __LINE__, FOCUSED, "suite", [&] {
            context->addSuite(__FILE__, __LINE__, NORMAL, "normal", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                    ++normal;
                });
            });
            context->addSuite(__FILE__, __LINE__, FOCUSED, "focused 1", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                    ++focused;
                });
            });
            context->addSuite(__FILE__, __LINE__, FOCUSED, "focused 2", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                    ++focused;
                });
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(focused).toBe(2);
        expect(normal).toBe(0);
    });

    it("should run all suites in a focused suite when no focused content", [&] {
        context->addSuite(__FILE__, __LINE__, FOCUSED, "suite", [&] {
            context->addSuite(__FILE__, __LINE__, NORMAL, "normal 1", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                    ++normal;
                });
            });
            context->addSuite(__FILE__, __LINE__, NORMAL, "normal 2", [&] {
                context->addTest(__FILE__, __LINE__, NORMAL, "test", [&] {
                    ++normal;
                });
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(normal).toBe(2);
    });

    it("should skip normal top level suites without focused content", [&] {
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite 1", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "normal", [&] {
                ++normal;
            });
        });
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite 2", [&] {
            context->addSuite(__FILE__, __LINE__, NORMAL, "sub suite", [&] {
                context->addSuite(__FILE__, __LINE__, NORMAL, "sub sub suite", [&] {
                    context->addTest(__FILE__, __LINE__, FOCUSED, "focused", [&] {
                        ++focused;
                    });
                });
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(focused).toBe(1);
        expect(normal).toBe(0);
    });

    it("should run focused top level suites without focused content", [&] {
        context->addSuite(__FILE__, __LINE__, FOCUSED, "suite 1", [&] {
            context->addTest(__FILE__, __LINE__, NORMAL, "normal", [&] {
                ++focused;
            });
        });
        context->addSuite(__FILE__, __LINE__, NORMAL, "suite 2", [&] {
            context->addSuite(__FILE__, __LINE__, NORMAL, "sub suite", [&] {
                context->addSuite(__FILE__, __LINE__, NORMAL, "sub sub suite", [&] {
                    context->addTest(__FILE__, __LINE__, FOCUSED, "focused", [&] {
                        ++focused;
                    });
                });
            });
        });
        context->run(ep);

        expect(context->isFailed()).toBeFalse();
        expect(focused).toBe(2);
    });
});
