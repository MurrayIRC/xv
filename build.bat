::===============================================================
:: Author: Rudy Faile @rfaile313
:: Description: Custom Run, Build, Clean, Debug Script
:: License: MIT
:: args in bat are %1, %2, etc - so run build means %1 is build
::===============================================================
@echo off

:: Determines output and launcher
SET EXECUTABLE=game.exe
:: Source to build from (can use abs or rel path)
SET SOURCE=C:\WORK\C\XV\SRC\main.c C:\WORK\C\XV\SRC\core.c

SET RAYLIB=C:\RAYLIB\RAYLIB\SRC

SET COMPILER=gcc
SET CFLAGS=-O1 -Wall -std=c99 -Wno-missing-braces
SET INCLUDEPATHS=-I %RAYLIB%
SET LIBPATHS=-L %RAYLIB%
SET LIBFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm

IF [%1] == [] GOTO RUN
IF [%1] == [clean] GOTO CLEAN
IF [%1] == [build] GOTO BUILD
IF [%1] == [debug] GOTO DEBUG
ECHO Invalid Command. Try run or run clean or run build or run debug
GOTO:EOF 

:RUN
IF NOT EXIST Build MKDIR Build
PUSHD Build
%COMPILER% %SOURCE% -o %EXECUTABLE% %CFLAGS% %WINFLAGS% %INCLUDEPATHS% %LIBPATHS% %LIBFLAGS% && echo **Build Successful. Running.** && echo. && %EXECUTABLE%
POPD
GOTO:EOF

:BUILD
IF NOT EXIST Build MKDIR Build
PUSHD Build
%COMPILER% %SOURCE% -o %EXECUTABLE% %CFLAGS% %WINFLAGS% %INCLUDEPATHS% %LIBPATHS% %LIBFLAGS% && echo **Build Successful** && echo.
POPD
GOTO:EOF 

:DEBUG
echo HAHA who needs a debugger (jk need to set up tinycc)
GOTO:EOF 

:CLEAN
IF NOT EXIST Build echo. && echo **No build directory at the moment**
IF EXIST Build RMDIR /Q/S Build && echo **Cleaned Build folder + files** 
GOTO:EOF 
