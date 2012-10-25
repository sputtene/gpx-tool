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
CPP     = $(TOOLCHAIN_PREFIX)cpp
CXX     = $(TOOLCHAIN_PREFIX)g++
LD      = $(TOOLCHAIN_PREFIX)ld
STRIP   = $(TOOLCHAIN_PREFIX)strip
WINDRES = $(TOOLCHAIN_PREFIX)windres

# Compiler and linker flags
CXXFLAGS += -O3 -Wall -Wextra -pedantic
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
        TOOLCHAIN_PREFIX = i686-w64-mingw32-
    else ifeq ($(TARGET), win64)
        TOOLCHAIN_PREFIX = x86_64-w64-mingw32-
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

%.d: %.cpp
	@echo Generating dependencies for $<
	@$(COMPILE.cpp) -MM $< -MF $@
	@mv -f $@ $@.tmp
	@sed -e 's|.*:|$*.o:|' < $@.tmp > $@
	@sed -e 's/.*://' -e 's/\\$$//' < $@.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $@
	@rm -f $@.tmp

%.d: %.rc
	@echo Generating dependencies for $<
	@# Use -x c, because otherwise gcc barfs on the .rc extension
	@$(COMPILE.c) -x c -MM $< -MF $@
	@mv -f $@ $@.tmp
	@sed -e 's|.*:|$*.o:|' < $@.tmp > $@
	@sed -e 's/.*://' -e 's/\\$$//' < $@.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $@
	@rm -f $@.tmp

debug_makefile:
	$(info Makefile variables:)
	$(info TARGET   = '$(TARGET)')
	$(info )
	$(info EXE      = '$(EXE)')
	$(info SOURCES  = '$(SOURCES)')
	$(info OBJS     = '$(OBJS)')
	$(info )
	$(info TOOLCHAIN_PREFIX = '$(TOOLCHAIN_PREFIX)')
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
