-include config.mk

TARGET      ?= SMACKW32.DLL

LDFLAGS     ?= -Wl,--enable-stdcall-fixup -s -shared -static
CFLAGS      ?= -masm=intel -O2 -Wall -march=pentium4 -D _WIN32_WINNT=0x0600
CXXFLAGS    ?= -masm=intel -O2 -Wall -march=pentium4 -D _WIN32_WINNT=0x0600
LIBS        ?= -lcomctl32

CC           = i686-w64-mingw32-gcc
CXX          = i686-w64-mingw32-g++
STRIP       ?= i686-w64-mingw32-strip
WINDRES     ?= i686-w64-mingw32-windres

SRCS     := $(wildcard src/*.c) $(wildcard src/*/*.c) res.rc
OBJS     := $(addsuffix .o, $(basename $(SRCS)))

.PHONY: all clean
all: $(TARGET)

%.o: %.rc
	$(WINDRES) -J rc $< $@ || windres -J rc $< $@

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ exports.def -L. $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET) || del $(TARGET) $(subst /,\\,$(OBJS))
