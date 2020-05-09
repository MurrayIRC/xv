.PHONY: all clean

PROJECT_NAME       ?= XV
RAYLIB_VERSION     ?= 3.0.0
RAYLIB_API_VERSION ?= 300
RAYLIB_PATH        ?= ..\..

# Define compiler path on Windows
COMPILER_PATH      ?= C:/mingw/bin

# No uname.exe on MinGW!, but OS=Windows_NT on Windows!
# ifeq ($(UNAME),Msys) -> Windows
ifeq ($(OS),Windows_NT)
	PLATFORM_OS=WINDOWS
	export PATH := $(COMPILER_PATH):$(PATH)
else
	UNAMEOS=$(shell uname)
	ifeq ($(UNAMEOS),Linux)
		PLATFORM_OS=LINUX
	endif
	ifeq ($(UNAMEOS),Darwin)
		PLATFORM_OS=OSX
	endif
endif

# Define default C compiler: gcc
# NOTE: define g++ compiler if using C++
CC = gcc

ifeq ($(PLATFORM_OS),OSX)
	# OSX default compiler
	CC = clang
endif

# Define default make program: Mingw32-make
MAKE = make

ifeq ($(PLATFORM_OS),WINDOWS)
	MAKE = mingw32-make
endif

# Define compiler flags:
#  -O0                  defines optimization level (no optimization, better for debugging)
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
CFLAGS = -std=c99 -g -O0 -Wall -Wno-missing-braces

# Additional flags for compiler (if desired)
#CFLAGS += -Wextra -Wmissing-prototypes -Wstrict-prototypes
ifeq ($(PLATFORM_OS),WINDOWS)
	# resource file contains windows executable icon and properties
	# -Wl,--subsystem,windows hides the console window
	CFLAGS += -Wl,--subsystem,windows
endif

ifeq ($(PLATFORM_OS),WINDOWS)
	# Libraries for Windows desktop compilation
	# NOTE: WinMM library required to set high-res timer resolution
	LIBRARIES = -L $(RAYLIB_PATH)/src -L lib -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
	# Required for physac examples
	#LDLIBS += -static -lpthread
endif
ifeq ($(PLATFORM_OS),OSX)
	# Libraries for OSX 10.9 desktop compiling
	# NOTE: Required packages: libopenal-dev libegl1-mesa-dev
	LIBRARIES = -L lib -lraylib -framework OpenGL -framework OpenAL -framework Cocoa -framework CoreVideo -framework IOKit -framework GLUT
endif


OUTPUT = build/game
SOURCES = src/main.c src/core.c
INCLUDES = -I $(RAYLIB_PATH)/src -I inc 
DEFINES = -DPLATFORM_DESKTOP

ifeq ($(PLATFORM_OS),OSX)
	DEFINES = -DSUPPORT_HIGH_DPI
endif

# Project target defined by PROJECT_NAME
all:
	$(MAKE) $(PROJECT_NAME)

$(PROJECT_NAME):
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCES) $(FRAMEWORKS) $(INCLUDES) $(LIBRARIES) $(DEFINES)

# Clean everything
clean:
ifeq ($(PLATFORM_OS),WINDOWS)
	del *.o *.exe /s
endif
ifeq ($(PLATFORM_OS),OSX)
	find . -type f -perm +ugo+x -delete
	rm -f *.o
endif