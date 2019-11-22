# Makefile Universal by Marc NGUYEN
# Project Name
TARGET?=$(shell basename $(CURDIR))

# Project structure
SRCDIR?=src
OBJDIR?=obj
LIBDIR?=lib
BINDIR?=bin

INC=-I.

DEBUG=

# C Compiler
CC?=clang
CFLAGS?=$(DEBUG) -Wall -Wextra -O3 $(INC)

# C++ Compiler
CXX?=clang++
CXXFLAGS?=$(DEBUG) -Wall -Wextra -O3 $(INC)

# Linker
LINKER?=$(CXX)
LFLAGS?=-Wall -Wextra $(INC) -L./$(LIBDIR)

# Get all files based on project structure
SOURCES:=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS:=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Cleaner
rm = rm -rf

# Link
$(BINDIR)/$(TARGET): $(OBJDIR)/main.o $(OBJECTS)
	@mkdir -p $(shell dirname $@)
	$(LINKER) $(LFLAGS) $^ -o $@
	@echo "Linking $@ complete!"

# Compile forEach C++
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: echoes
echoes:
	@echo "OBJECTS :"
	@echo "$(OBJECTS)"
	@echo "SOURCES :"
	@echo "$(SOURCES)"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR)
	@$(rm) $(LIBDIR)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
