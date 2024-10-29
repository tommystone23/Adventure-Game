# Compiler and Linker
CXX         := g++
CC          := gcc

# The Target Binary Program
TARGET      := out

# The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := include
LIBDIR		:= lib
BUILDDIR    := obj
TARGETDIR   := bin
SRCEXT_CPP  := cpp
SRCEXT_C    := c
OBJEXT      := o

# Flags, Libraries, and Includes
CXXFLAGS    := -Wall -std=c++11
CFLAGS      := -Wall
LIB         := -lGL -lSDL2 -lSDL2_mixer -lSDL2_ttf -ldl
INC         := -I$(INCDIR) -I/usr/local/include
LIB_BIN 	:= -L$(LIBDIR)
RUNTIME_LIB	:= -Wl,-rpath=$(LIBDIR)

# Find source and object files
SOURCES_CPP := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT_CPP))
SOURCES_C   := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT_C))
SOURCES     := $(SOURCES_CPP) $(SOURCES_C)
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_CPP:.$(SRCEXT_CPP)=.$(OBJEXT)))
OBJECTS     += $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_C:.$(SRCEXT_C)=.$(OBJEXT)))

# Default Make
all: directories $(TARGET)

# Remake
remake: cleaner all

# Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

# Clean only objects
clean:
	@$(RM) -rf $(BUILDDIR)

# Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

# Run the program
run: all
	./$(TARGETDIR)/$(TARGET)

# Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

# Link
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGETDIR)/$(TARGET) $^ $(LIB_BIN) $(LIB) $(RUNTIME_LIB)

# Compile C++ files
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT_CPP)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

# Compile C files
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT_C)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Non-File Targets
.PHONY: all remake clean cleaner run

