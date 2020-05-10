.PHONY: all clean

PROJECT_NAME       ?= xv
RAYLIB_VERSION     ?= 3.0.0
RAYLIB_API_VERSION ?= 300
RAYLIB_PATH        ?= ..\..
PLATFORM           ?= PLATFORM_DESKTOP

BUILD_MODE            ?= RELEASE
RAYLIB_RELEASE_PATH 	?= $(RAYLIB_PATH)/src

# Define compiler path on Windows
COMPILER_PATH      ?= C:/raylib/mingw/bin 

# Determine PLATFORM_OS in case PLATFORM_DESKTOP selected
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    # No uname.exe on MinGW!, but OS=Windows_NT on Windows!
    # ifeq ($(UNAME),Msys) -> Windows
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS=WINDOWS
        export PATH := $(COMPILER_PATH):$(PATH)
    else
        UNAMEOS=$(shell uname)
        ifeq ($(UNAMEOS),Darwin)
            PLATFORM_OS=OSX
        endif
    endif
endif

# Define default C compiler: gcc
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
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -std=gnu99           defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
#  -D_DEFAULT_SOURCE    use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
CFLAGS += -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces
ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g
else
	CFLAGS += -O1
endif
# Additional flags for compiler (if desired)
#CFLAGS += -Wextra -Wmissing-prototypes -Wstrict-prototypes
ifeq ($(PLATFORM_OS),WINDOWS)
	# resource file contains windows executable icon and properties
	# -Wl,--subsystem,windows hides the console window
	CFLAGS += -Wl,--subsystem,windows
endif

LIBRARIES = -Llib -lraylib
ifeq ($(PLATFORM_OS),WINDOWS)
	# Libraries for Windows desktop compilation
	LIBRARIES += -lopengl32 -lgdi32 -lwinmm -static -lpthread
endif
ifeq ($(PLATFORM_OS),OSX)
	# Libraries for OSX 10.9 desktop compiling
	# NOTE: Required packages: libopenal-dev libegl1-mesa-dev
	LIBRARIES += -framework OpenGL -framework OpenAL -framework Cocoa -framework CoreVideo -framework CoreAudio -framework IOKit
endif

OUTPUT = build/$(PROJECT_NAME)
SOURCES = src/main.c src/core.c
INCLUDES = -Iinc
DEFINES = -DPLATFORM_DESKTOP

ifeq ($(PLATFORM_OS),OSX)
	DEFINES = -DSUPPORT_HIGH_DPI
endif

# Project target defined by PROJECT_NAME
all:
	$(CC) -o $(OUTPUT) $(SOURCES) $(CFLAGS) $(INCLUDES) $(LIBRARIES) $(DEFINES)

# Clean everything
clean:
ifeq ($(PLATFORM_OS),WINDOWS)
	del *.o *.exe /s
endif
ifeq ($(PLATFORM_OS),OSX)
	find . -type f -perm +ugo+x -delete
	rm -f *.o
endif