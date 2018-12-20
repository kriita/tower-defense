# compiler (must support -MM -MT -MF -I -c and -o flags)
CXX := g++

WARN := -Wall -Wextra -Weffc++ -Wpedantic
LIBS := -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

# flags, note that $(FLAGS) is empty unless specified in the prompt
# i.e. one can write: 'make all FLAGS="-g -O0"' for example
CXXFLAGS := -std=c++17 $(WARN) -O3 -L${SFML_ROOT}/lib -I${SFML_ROOT}/include

# name of executable
OUT := run

# this is the directory I will compile from (i.e. the argument to -I)
IDIR := include

# source directory, this is where I will look for sources
SRC  := src

# test source directory
TEST_SRC  := test

# file which contains the main function
MAINFILE := main.cpp

# file which contains the main function
TEST_MAINFILE := test_main.cpp

# all object files will be put here
ODIR := .objs

# all binaries will be put here
BIN  := bin

# all dependency files will be put here
DDIR := .dependencies

# all targets that do not have dependencies
NODEPS := clean reset sources test_sources objects clean-dep

# suffix of sources I will look for
SUF := cpp cxx cc c

# INITIALIZATION

SOURCES := $(foreach suf,$(SUF), $(shell find $(SRC)/ -name "*.$(suf)" ! -name "$(MAINFILE)" ! -name "$(TEST_MAINFILE)" ! -name "*test.$(suf)"))
DEPFILES := $(patsubst %,$(DDIR)/%.d,$(SOURCES))
OBJS := $(patsubst %,$(ODIR)/%.o,$(SOURCES))
TEST_SOURCES := $(foreach suf,$(SUF), $(shell find $(SRC)/ -name "*.$(suf)" ! -name "$(MAINFILE)"))
TEST_DEPFILES := $(patsubst %,$(DDIR)/%.d,$(TEST_SOURCES))
TEST_OBJS := $(patsubst %,$(ODIR)/%.o,$(TEST_SOURCES))

# MAIN TARGET

all: $(OBJS) $(SRC)/$(MAINFILE) $(DEPFILES)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -I$(IDIR) $(OBJS) $(SRC)/$(MAINFILE) -o $(BIN)/$(OUT) $(LIBS) $(FLAGS) 

# TEST FILES

all_tests: $(TEST_OBJS) $(TEST_DEPFILES)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -I$(IDIR) $(TEST_OBJS) -o $(BIN)/all_tests $(LIBS) $(FLAGS) 

map_test: $(OBJS) $(SRC)/$(TEST_SRC)/map_test.cpp $(ODIR)/$(SRC)/$(TEST_SRC)/$(TEST_MAINFILE).o
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -I$(IDIR) $(OBJS) $(SRC)/$(TEST_SRC)/map_test.cpp $(ODIR)/$(SRC)/$(TEST_SRC)/$(TEST_MAINFILE).o -o $(BIN)/map_test $(LIBS) $(FLAGS) 

projectile_test: $(OBJS) $(SRC)/$(TEST_SRC)/projectile_test.cpp $(ODIR)/$(SRC)/$(TEST_SRC)/$(TEST_MAINFILE).o
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -I$(IDIR) $(OBJS) $(SRC)/$(TEST_SRC)/projectile_test.cpp $(ODIR)/$(SRC)/$(TEST_SRC)/$(TEST_MAINFILE).o -o $(BIN)/projectile_test $(LIBS) $(FLAGS)

monster_test: $(OBJS) $(SRC)/$(TEST_SRC)/monster_test.cpp $(ODIR)/$(SRC)/$(TEST_SRC)/$(TEST_MAINFILE).o
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -I$(IDIR) $(OBJS) $(SRC)/$(TEST_SRC)/monster_test.cpp $(ODIR)/$(SRC)/$(TEST_SRC)/$(TEST_MAINFILE).o -o $(BIN)/monster_test $(LIBS) $(FLAGS)

# DEBUG TARGET
debug: CXXFLAGS += -g -O0
debug: all

# if the supplied goal has no dependencies, then ignore the
# dependencies
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
    -include $(DEPFILES)
endif

# BUILD DEPENDENCIES FILES
# build dependencies if they do not exist or are out of date
.PRECIOUS: $(DDIR)/%.d
$(DDIR)/%.d: %
	@mkdir -p $(dir $@)
	@echo "Finding dependencies for $<..."
	@$(CXX) $(CXXFLAGS) -I$(IDIR) -MM -MT '$(patsubst %,$(ODIR)/%.o,$<)' $< -MF $@ $(LIBS) $(FLAGS)

# BUILD OBJECT FILES

$(ODIR)/%.o: % $(DDIR)/%.d
	@echo "Compiling $@..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(IDIR) $< -o $@ -c $(LIBS) $(FLAGS) 

# OTHERS

.PHONY: clean reset sources test_sources objects clean-dep

sources:
	@echo $(SOURCES) $(SRC)/$(MAINFILE)

test_sources:
	@echo $(TEST_SOURCES) $(SRC)/test/$(TEST_MAINFILE)

objects:
	@echo "$(OBJS)"

# REMOVE OBJECT FILES
clean:
	rm -f $(OBJS)
	@(test -d $(ODIR) && rmdir --ignore-fail-on-non-empty -p $(ODIR)/* && echo "rmdir --ignore-fail-on-non-empty -p $(ODIR)/*") || true

reset: 
	rm -rf $(BIN) $(ODIR) $(DDIR)

clean-dep:
	rm -rf $(DDIR)
