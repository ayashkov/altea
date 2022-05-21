#ifndef __ALTEA_HH
#define __ALTEA_HH

#include <string>
#include <functional>
#include <queue>
#include <vector>
#include <exception>

namespace altea {
    enum Mode { NORMAL, FOCUSED, EXCLUDED };

    class SourceMessage {
    public:
        const std::string file;

        const int line;

        const std::string type;

        const std::string message;

        SourceMessage(const std::string &file, int line,
            const std::string &type, const std::string &message):
            file(file), line(line), type(type), message(message)
        {
        }

        operator std::string() const
        {
            return type + ": " + message + " @" + file + ":" +
                std::to_string(line);
        }
    };

    class TestException: public std::exception {
    public:
        TestException(): std::exception()
        {
        }
    };

    class SyntaxException: public TestException {
    public:
        const std::string message;

        SyntaxException(const std::string &file, int line,
            const std::string &message): TestException(),
            message(SourceMessage(file, line, "Syntax error", message))
        {
        }

        virtual const char *what() const noexcept
        {
            return message.c_str();
        }
    };

    class Matcher {
    public:
        Matcher(const std::string &file, int line);

        void nothing();

        void toFail(const std::string &description);
    private:
        std::string file;

        int line;
    };

    class Testable {
    public:
        const std::string file;

        const int line;

        const std::string description;

        Testable(const std::string &file, int line, Mode mode,
            const std::string &description,
            std::function<void (void)> testable);

        virtual ~Testable()
        {
        }

        bool skipped(bool focusedMode);

        void test();

        void recordExpect();

        void addFailure(SourceMessage &failure);

        virtual void addBeforeAll(const std::string &file, int line,
            std::function<void (void)> setup) = 0;

        virtual void addBeforeEach(const std::string &file, int line,
            std::function<void (void)> setup) = 0;

        virtual void addAfterAll(const std::string &file, int line,
            std::function<void (void)> teardown) = 0;

        virtual void addAfterEach(const std::string &file, int line,
            std::function<void (void)> teardown) = 0;

        virtual void addSuite(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> suite) = 0;

        virtual void addTest(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> test) = 0;

        virtual Matcher doExpect(const std::string &file, int line)
            const = 0;

        virtual void evaluate() const;

    protected:
        Mode mode;

        std::function<void (void)> testable;

        int expectCount = 0;

        std::vector<SourceMessage> failures;
    };

    class Test: public Testable {
    public:
        Test(const std::string &file, int line, Mode mode,
            const std::string &description,
            std::function<void (void)> test);

        virtual void addBeforeAll(const std::string &file, int line,
            std::function<void (void)> setup);

        virtual void addBeforeEach(const std::string &file, int line,
            std::function<void (void)> setup);

        virtual void addAfterAll(const std::string &file, int line,
            std::function<void (void)> teardown);

        virtual void addAfterEach(const std::string &file, int line,
            std::function<void (void)> teardown);

        virtual void addSuite(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> suite);

        virtual void addTest(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> test);

        virtual Matcher doExpect(const std::string &file, int line) const;

        virtual void evaluate() const;
    };

    class Suite: public Testable {
    public:
        Suite(const std::string &file, int line, Mode mode,
            const std::string &description,
            std::function<void (void)> suite);

        virtual ~Suite();

        inline Suite *with(std::function<void (void)> suite)
        {
            testable = suite;

            return this;
        }

        virtual void addBeforeAll(const std::string &file, int line,
            std::function<void (void)> setup);

        virtual void addBeforeEach(const std::string &file, int line,
            std::function<void (void)> setup);

        virtual void addAfterAll(const std::string &file, int line,
            std::function<void (void)> teardown);

        virtual void addAfterEach(const std::string &file, int line,
            std::function<void (void)> teardown);

        virtual void addSuite(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> suite);

        virtual void addTest(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> test);

        virtual Matcher doExpect(const std::string &file, int line) const;

        void rootRun();

    private:
        bool focusedMode = false;

        int discovered = 0;

        std::queue<Suite*> subSuites;

        std::vector<std::function<void (void)>> beforeAll;

        std::vector<std::function<void (void)>> beforeEach;

        std::vector<std::function<void (void)>> afterAll;

        std::vector<std::function<void (void)>> afterEach;

        std::vector<Testable*> testables;

        void adjustMode(Mode mode);

        void add(std::function<void(void)> mutator);

        bool isLastCall();

        void run();

        void runOne(Testable *testable);
    };

    class Context {
    public:
        Context();

        ~Context();

        inline Testable *updateCurrent(Testable *next)
        {
            auto prev = current;

            current = next;

            return prev;
        }

        inline bool isDiscovery() const
        {
            return discovery;
        }

        inline bool isFailed() const
        {
            return failed;
        }

        inline void addBeforeAll(const std::string &file, int line,
            std::function<void (void)> setup)
        {
            current->addBeforeAll(file, line, setup);
        }

        inline void addBeforeEach(const std::string &file, int line,
            std::function<void (void)> setup)
        {
            current->addBeforeEach(file, line, setup);
        }

        inline void addAfterAll(const std::string &file, int line,
            std::function<void (void)> teardown)
        {
            current->addAfterAll(file, line, teardown);
        }

        inline void addAfterEach(const std::string &file, int line,
            std::function<void (void)> teardown)
        {
            current->addAfterEach(file, line, teardown);
        }

        inline void addSuite(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> suite)
        {
            current->addSuite(file, line, mode, description, suite);
        }

        inline void addTest(const std::string &file, int line,
            Mode mode, const std::string &description,
            std::function<void (void)> test)
        {
            current->addTest(file, line, mode, description, test);
        }

        inline Matcher doExpect(const std::string &file, int line)
        {
            return current->doExpect(file, line);
        }

        void run();

        void recordExpect();

        void log(const std::string &message);

        void recordFailure(const std::string &file, int line,
            const std::string &message);

    private:
        Suite root;

        Testable *current;

        bool discovery = true;

        bool failed = false;
    };

    extern Context __context__;
}

#define beforeAll(setup) (__context__.addBeforeAll(__FILE__, __LINE__, \
    setup))
#define beforeEach(setup) (__context__.addBeforeEach(__FILE__, __LINE__, \
    setup))
#define afterAll(teardown) (__context__.addAfterAll(__FILE__, __LINE__, \
    teardown))
#define afterEach(teardown) (__context__.addAfterEach(__FILE__, \
    __LINE__, teardown))
#define describe(description, suite) (__context__.addSuite(__FILE__, \
    __LINE__, NORMAL, description, suite), 0)
#define fdescribe(description, suite) (__context__.addSuite(__FILE__, \
    __LINE__, FOCUSED, description, suite), 0)
#define xdescribe(description, suite) (__context__.addSuite(__FILE__, \
    __LINE__, EXCLUDED, description, suite), 0)
#define it(description, test) (__context__.addTest(__FILE__, __LINE__, \
    NORMAL, description, test))
#define fit(description, test) (__context__.addTest(__FILE__, __LINE__, \
    FOCUSED, description, test))
#define xit(description, test) (__context__.addTest(__FILE__, __LINE__, \
    EXCLUDED, description, test))
#define expect() (__context__.doExpect(__FILE__, __LINE__))
#define fail(message) (__context__.doExpect(__FILE__, __LINE__) \
    .toFail(message))

#endif // __ALTEA_HH
