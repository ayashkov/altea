# directories
SRC=src
SPEC=test
TARGET=target
BIN=$(TARGET)/bin
TEST=$(TARGET)/test

# tools
RANLIB=ranlib
MKDIR=mkdir
RM=rm

.PHONY: all test clean

$(BIN)/%.o: $(SRC)/%.cc $(BIN)
	$(CXX) -std=c++17 -I$(SRC) -c -o $@ $<

$(TEST)/%.o: $(SPEC)/%.cc $(TEST)
	$(CXX) -std=c++17 -I$(SPEC) -I$(SRC) -c -o $@ $<

all: test

test: $(TEST)/altea
	$(TEST)/altea

$(BIN)/libaltea.a: $(BIN)/context.o $(BIN)/testable.o $(BIN)/suite.o \
	$(BIN)/test.o $(BIN)/matchers.o
	$(AR) -cr $@ $^
	$(RANLIB) $@

$(TEST)/altea: $(BIN)/libaltea.a $(TEST)/spec1.o $(TEST)/context.o
	$(CXX) -o $@ $+

$(BIN):
	$(MKDIR) -p $@

$(TEST):
	$(MKDIR) -p $@

$(BIN)/context.o: $(SRC)/altea.hh

$(BIN)/testable.o: $(SRC)/altea.hh

$(BIN)/suite.o: $(SRC)/altea.hh

$(BIN)/test.o: $(SRC)/altea.hh

$(BIN)/matchers.o: $(SRC)/altea.hh

clean:
	$(RM) -rf $(TARGET)
