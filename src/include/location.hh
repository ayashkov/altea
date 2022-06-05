#ifndef __LOCATION_HH
#define __LOCATION_HH

#include <string>

namespace altea {
    class Location {
    public:
        const std::string file;

        const int line;

        Location(const std::string &file, const int line):
            file(file), line(line)
        {
        }

        operator std::string() const
        {
            return "@" + file + ":" + std::to_string(line);
        }
    };
}

#endif // __LOCATION_HH
