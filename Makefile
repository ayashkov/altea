# directories
SRC = src
INCLUDE = src/include
SPEC = test

TARGET = target

SRCS := $(notdir $(wildcard $(SRC)/*.cc))
SPECS := $(notdir $(wildcard $(SPEC)/*.cc))
OBJS := $(patsubst %.cc,$(TARGET)/%.o,$(SRCS))
TESTS := $(patsubst %.cc,$(TARGET)/%.o,$(SPECS))

# options
CXXFLAGS = -std=c++17 -MMD -MP
CPPFLAGS = -I$(INCLUDE)

# tools
RANLIB=ranlib
MKDIR=mkdir
RM=rm

vpath %.spec.cc $(SPEC)
vpath %.cc $(SRC)

.PHONY: all test clean

all: $(TARGET)/libaltea.a $(TARGET)/libaltea.so

test: $(TARGET)/altea.altea
	$(TARGET)/altea.altea

$(TARGET):
	$(MKDIR) -p $@

$(TARGET)/%.o: %.cc | $(TARGET)
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

clean:
	$(RM) -rf $(TARGET)

$(TARGET)/libaltea.a: $(OBJS)
	$(AR) -cr $@ $^
	$(RANLIB) $@

$(TARGET)/libaltea.so: $(TARGET)/libaltea.a
	$(LINK.cc) -shared -o $@ $^

$(TARGET)/altea.altea: $(TARGET)/libaltea.a $(TESTS)
	$(LINK.cc) -o $@ $^

-include $(patsubst %.cc,$(TARGET)/%.d,$(SRCS))
