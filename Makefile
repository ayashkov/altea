# directories
SRC = src
INCLUDE = src/include
SPEC = test

TARGET = target
BIN = $(TARGET)/bin
TEST = $(TARGET)/test

SRCS := $(notdir $(wildcard $(SRC)/*.cc))
SPECS := $(notdir $(wildcard $(SPEC)/*.cc))
OBJS := $(patsubst %.cc,%.o,$(SRCS))
TESTS := $(patsubst %.cc,%.o,$(SPECS))

# options
CXXFLAGS = -std=c++17 -MMD -MP
CPPFLAGS = -I$(INCLUDE)

# tools
RANLIB=ranlib
MKDIR=mkdir
RM=rm

vpath %.spec.cc $(SPEC)
vpath %.cc $(SRC)
vpath %.hh $(INCLUDE)

.PHONY: all test clean

all: libaltea.a libaltea.so

test: altea.altea
	./altea.altea

clean:
	$(RM) -f *.d
	$(RM) -f *.o
	$(RM) -f *.a
	$(RM) -f *.so
	$(RM) -f *.altea

libaltea.a: $(OBJS)
	$(AR) -cr $@ $^
	$(RANLIB) $@

libaltea.so: libaltea.a
	$(LINK.cc) -shared -o $@ $^

altea.altea: libaltea.a $(TESTS)
	$(LINK.cc) -o $@ $^

-include $(patsubst %.cc,%.d,$(SRCS))
