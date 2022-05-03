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

$(BIN)/%.o: $(SRC)/%.cc $(BIN)
	$(CXX) -std=c++17 -I$(SRC) -c -o $@ $<

$(TEST)/%.o: $(SPEC)/%.cc $(TEST)
	$(CXX) -std=c++17 -I$(SPEC) -I$(SRC) -c -o $@ $<

all: test

test: $(TEST)/altea
	$(TEST)/altea

$(BIN)/libaltea.a: $(BIN)/altea.o
	$(AR) -cr $@ $^
	$(RANLIB) $@

$(TEST)/altea: $(BIN)/libaltea.a $(TEST)/altea-poc1.spec.o $(TEST)/altea-poc2.spec.o
	$(CXX) -o $@ $+

$(BIN):
	$(MKDIR) -p $@

$(TEST):
	$(MKDIR) -p $@

$(BIN)/altea.o: $(SRC)/altea.hh

.PHONY: clean
clean:
	$(RM) -rf $(TARGET)
