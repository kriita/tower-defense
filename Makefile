# compiler (must support -MM -MT -MF -I -c and -o flags)
CXX := g++

WARN := -Wall -Wextra -Weffc++ -Wpedantic
LIBS := -lsfml-window -lsfml-graphics -lsfml-system

# flags, note that $(FLAGS) is empty unless specified in the prompt
# i.e. one can write: 'make all FLAGS="-g -O0"' for example
CXXFLAGS := -std=c++17 $(WARN) -O3 -L${SFML_ROOT}/lib -I${SFML_ROOT}/include

# name of executable
OUT := run

# this is the directory I will compile from (i.e. the argument to -I)
IDIR := include

# source directory, this is where I will look for sources
SRC  := src

# file which contains the main function
MAINFILE := main.cpp

# all object files will be put here
ODIR := .objs

# all binaries will be put here
BIN  := bin

# all dependency files will be put here
DDIR := .dependencies

# all targets that do not have dependencies
NODEPS := clean reset sources objects clean-dep

# suffix of sources I will look for
SUF := cpp cxx cc c

# INITIALIZATION

SOURCES := $(foreach suf,$(SUF), $(shell find $(SRC)/ -name "*.$(suf)" -not -name "$(MAINFILE)"))
DEPFILES := $(patsubst %,$(DDIR)/%.d,$(SOURCES))
OBJS := $(patsubst %,$(ODIR)/%.o,$(SOURCES))

# MAIN TARGET

all: $(OBJS) $(SRC)/$(MAINFILE) $(DEPFILES)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -I$(IDIR) $(OBJS) $(SRC)/$(MAINFILE) -o $(BIN)/$(OUT) $(LIBS) $(FLAGS) 

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

.PHONY: clean reset sources objects clean-dep

sources:
	@echo $(SOURCES) $(SRC)/$(MAINFILE)

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
