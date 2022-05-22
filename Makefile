# directories
SRC = src
INCLUDE = src/include
SPEC = test
TARGET = target

SRCS := $(wildcard $(SRC)/*.cc)
SPECS := $(wildcard $(SPEC)/*.cc)
OBJS := $(patsubst %.cc,$(TARGET)/%.o,$(notdir $(SRCS)))
TESTS := $(patsubst %.cc,$(TARGET)/%.o,$(notdir $(SPECS)))

# options
CXXFLAGS = -std=c++17 -MMD -MP
CPPFLAGS = -I$(INCLUDE)

# tools
RANLIB=ranlib
MKDIR=mkdir
RM=rm

.PHONY: all test clean

all: $(TARGET)/libaltea.a $(TARGET)/libaltea.so

test: $(TARGET)/altea.altea
	$(TARGET)/altea.altea

$(TARGET):
	$(MKDIR) -p $@

$(TARGET)/%.o: $(SRC)/%.cc | $(TARGET)
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

$(TARGET)/%.o: $(SPEC)/%.cc | $(TARGET)
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

clean:
	$(RM) -rf $(TARGET)

$(TARGET)/libaltea.a: $(OBJS)
	$(AR) -cr $@ $^
	$(RANLIB) $@

$(TARGET)/libaltea.so: $(OBJS)
	$(LINK.cc) -shared -o $@ $^

$(TARGET)/altea.altea: $(TARGET)/libaltea.a $(TESTS)
	$(LINK.cc) -o $@ $^

-include $(patsubst %.o,%.d,$(OBJS))
