====================================================================
 UDRMS - University Dormitory & Restaurant Management System
 ENSIA 2025-2026 - Object-Oriented Programming Project
====================================================================

WHAT IS THIS?
--------------------------------------------------------------------
UDRMS is a C++ program that manages a university's dormitories,
rooms, students, and restaurants. You can add dormitories, assign
students to rooms, set up restaurant menus, and track meals served.
Everything is saved automatically to text files so your data is
still there next time you run the program.

There are two ways to use it:
  1. Console version (text menus in a terminal) - always available
  2. GUI version (a proper window with buttons) - only if you have
     Qt 6 installed


FOLDER LAYOUT
--------------------------------------------------------------------
UDRMS/
  CMakeLists.txt     - build configuration
  Makefile           - alternative build file for mingw32-make
  include/           - header files (.h)
  src/               - program logic (.cpp)
  ui/                - GUI files (only used if building with Qt)
  data/              - where your saved data lives (created
                        automatically, don't worry about it)


HOW TO BUILD AND RUN IT (Windows)
--------------------------------------------------------------------
You need ONE of the following already installed:
  - Visual Studio with the "Desktop development with C++" workload
  - MinGW with g++ and mingw32-make

OPTION A - Using mingw32-make (simplest if you already have it)
  1. Open a terminal in the UDRMS folder
  2. Type:
         mingw32-make
  3. Run the program:
         UDRMS.exe

  To rebuild from scratch:
         mingw32-make clean
         mingw32-make

OPTION B - Using Visual Studio
  1. Open Visual Studio
  2. File > Open > CMake...
  3. Select the CMakeLists.txt file inside the UDRMS folder
  4. Visual Studio sets everything up automatically
  5. Pick "UDRMS.exe" from the run menu at the top and press F5

OPTION C - Using CMake from the command line
  1. Open "Developer Command Prompt for VS" (search for it in the
     Start menu)
  2. Type:
         cd path\to\UDRMS
         mkdir build
         cd build
         cmake ..
         cmake --build . --config Release
  3. Run it:
         .\Release\UDRMS.exe


WANT THE GUI VERSION INSTEAD?
--------------------------------------------------------------------
This needs Qt 6 installed (free download from qt.io). Once Qt is
installed, build with CMake and point it to your Qt folder, e.g.:

         cmake .. -DCMAKE_PREFIX_PATH=C:\Qt\6.7.0\mingw_64
         cmake --build .
         UDRMS_GUI.exe

If you don't have Qt, no problem - the console version works the
same way, just with text menus instead of buttons.


YOUR DATA
--------------------------------------------------------------------
Everything you create (dormitories, students, restaurants, menus)
is saved automatically into the "data" folder as plain text files.
You don't need to do anything manually - it loads when you open
the program and saves when you close it (or use the Save option).


THAT'S IT
--------------------------------------------------------------------
If something doesn't compile, double check you have a C++17
compiler installed (g++, clang, or Visual Studio's compiler) and
that you're running the build commands from inside the UDRMS
folder, not from a folder above or below it.
