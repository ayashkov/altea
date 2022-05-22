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
CXXFLAGS = -std=c++17
CPPFLAGS = -I$(INCLUDE)

# tools
RANLIB=ranlib
MKDIR=mkdir
RM=rm

vpath %.spec.cc $(SPEC)
vpath %.cc $(SRC)
vpath %.hh $(INCLUDE)

.PHONY: all test clean

all: test

test: altea
	./altea

clean:
	$(RM) -f altea
	$(RM) -f *.o
	$(RM) -f *.a

libaltea.a: $(OBJS)
	$(AR) -cr $@ $^
	$(RANLIB) $@

altea: libaltea.a $(TESTS)
	$(LINK.cc) -o $@ $^
