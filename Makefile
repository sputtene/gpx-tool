# Makefile to build gpx-tool
# ==========================
# This Makefile enables easy building of the gpx-tool by setting up
# the correct values for $CC, $LD, ... for MinGW cross-compiling.


##########
### General configuration
##########
# Files
EXE      = gpx-tool$(EXE_SUFFIX)
SOURCES  = $(wildcard src/*.cpp) src/irrxml-1.2/src/irrXML.cpp
OBJS     = $(patsubst %.cpp, %.o, $(filter %.cpp, $(SOURCES)))

# Toolchain
CPP     = $(CROSS)cpp
CC      = $(CROSS)gcc
CXX     = $(CROSS)g++
LD      = $(CROSS)ld
STRIP   = $(CROSS)strip
WINDRES = $(CROSS)windres

# Compiler and linker flags
CPPFLAGS += -MP -MD
CXXFLAGS += -O0 -Wall -Wextra -pedantic -ggdb3
LDFLAGS  +=


##########
### Platform specific
##########
ifndef TARGET
    TARGET := win32
endif

ifneq ($(findstring $(TARGET), win32 win64),)
    # One of the windows targets is selected
    # Compiler and linker flags
    CXXFLAGS += -mwindows -fshort-wchar -DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x0500
    # http://gcc.gnu.org/bugzilla/show_bug.cgi?id=40376
    CXXFLAGS += -municode -DUNICODE -D_UNICODE
    LDFLAGS  += -static-libgcc -static-libstdc++
    LDLIBS   += -lcomctl32

    # Extra files to compile
    EXE_SUFFIX  = .exe
    SOURCES    += $(wildcard src/windows/*.cpp src/windows/*.rc)
    OBJS       += $(patsubst %.rc, %.o, $(filter %.rc, $(SOURCES)))

    # Use appropriate cross-compiler toolchain
    ifeq ($(TARGET), win32)
        CROSS = i686-w64-mingw32-
    else ifeq ($(TARGET), win64)
        CROSS = x86_64-w64-mingw32-
    else
        $(error Makefile error: $$TARGET = "$(TARGET)"
    endif
else
    $(info Unknown target "$(TARGET)")
    $(MAKE) info
endif


##########
### Make rules
##########
all: $(EXE)

info:
	$(info Set $$TARGET environment to one of the following:)
	$(info - win32: build 32bit Windows executable)
	$(info - win64: build 64bit Windows executable)
	@exit 0

clean:
	rm -f $(EXE)
	rm -f $(OBJS)
	rm -f $(OBJS:.o=.d)

$(EXE): $(OBJS)
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(OBJS): Makefile

%.o: %.rc %.h
	@# TODO: implement --language <val>
	$(WINDRES) -i $< -o $@

%.d: %.rc
	$(CC) -xc -MP -M $< -MF $@

debug_makefile:
	$(info Makefile variables:)
	$(info TARGET   = '$(TARGET)')
	$(info )
	$(info EXE      = '$(EXE)')
	$(info SOURCES  = '$(SOURCES)')
	$(info OBJS     = '$(OBJS)')
	$(info )
	$(info CROSS    = '$(CROSS)')
	$(info CPP      = '$(CPP)')
	$(info CXX      = '$(CXX)')
	$(info LD       = '$(LD)')
	$(info STRIP    = '$(STRIP)')
	$(info WINDRES  = '$(WINDRES)')
	$(info CXXFLAGS = '$(CXXFLAGS)')
	$(info LDFLAGS  = '$(LDFLAGS)')
	@exit 0

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

.PHONY: all info clean debug_makefile
