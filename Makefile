CC = clang

# Define compiler flags:
#  -O0                  defines optimization level (no optimization, better for debugging)
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
CFLAGS = -std=c99 -g -O0 -Wall -Wno-missing-braces

OUTPUT = build/game
SOURCES = src/main.c src/core.c
FRAMEWORKS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
INCLUDES = -I inc
LIBRARIES = -L lib -lraylib
DEFINES = -DPLATFORM_DESKTOP -DSUPPORT_HIGH_DPI

# Project target defined by PROJECT_NAME
game:
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCES) $(FRAMEWORKS) $(INCLUDES) $(LIBRARIES) $(DEFINES)