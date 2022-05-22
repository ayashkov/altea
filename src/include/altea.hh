#ifndef __ALTEA_HH
#define __ALTEA_HH

#include "context.hh"

namespace altea {
    extern Context __context__;
}

#define beforeAll(setup) (__context__.addBeforeAll(__FILE__, __LINE__, \
    (setup)))
#define beforeEach(setup) (__context__.addBeforeEach(__FILE__, __LINE__, \
    (setup)))
#define afterAll(teardown) (__context__.addAfterAll(__FILE__, __LINE__, \
    (teardown)))
#define afterEach(teardown) (__context__.addAfterEach(__FILE__, \
    __LINE__, (teardown)))
#define describe(description, suite) (__context__.addSuite(__FILE__, \
    __LINE__, NORMAL, (description), (suite)), 0)
#define fdescribe(description, suite) (__context__.addSuite(__FILE__, \
    __LINE__, FOCUSED, (description), (suite)), 0)
#define xdescribe(description, suite) (__context__.addSuite(__FILE__, \
    __LINE__, EXCLUDED, (description), (suite)), 0)
#define it(description, test) (__context__.addTest(__FILE__, __LINE__, \
    NORMAL, (description), (test)))
#define fit(description, test) (__context__.addTest(__FILE__, __LINE__, \
    FOCUSED, (description), (test)))
#define xit(description, test) (__context__.addTest(__FILE__, __LINE__, \
    EXCLUDED, (description), (test)))
#define expect(obj...) (__context__.doExpect(__FILE__, __LINE__, ##obj))
#define fail(message) (__context__.doExpect(__FILE__, __LINE__) \
    .toFail(message))

#endif // __ALTEA_HH
