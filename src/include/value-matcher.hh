#ifndef __VALUE_MATCHER_HH
#define __VALUE_MATCHER_HH

#include <string>

#include "base-matcher.hh"

namespace altea {
    template <typename T>
    inline std::string toString(const T &value)
    {
        return std::to_string(value);
    }

    template <>
    inline std::string toString(const std::string &value)
    {
        return value;
    }

    template <typename M, typename T>
    class ValueMatcher: public BaseMatcher {
    public:
        void toBe(const T &expected)
        {
            recordExpect();

            if ((value == expected) == negated)
                recordFailure(describe("to be", expected));
        }

        M NOT()
        {
            return M(location, test, !negated, value);
        }

    protected:
        ValueMatcher(const Location &location, Test *const test,
            const bool negated, const T &value): BaseMatcher(location, test),
            negated(negated), value(value)
        {
        }

    private:
        const T value;

        const bool negated;

        std::string describe(const std::string &eval, const T &expected)
        {
            std::string descr = "expected the value ";

            if (negated)
                descr += "NOT ";

            descr += eval + " <" + toString(expected) +
                ">, but it was <" + toString(value) + ">";

            return descr;
        }
    };
}

#endif // __VALUE_MATCHER_HH
