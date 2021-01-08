cmake_minimum_required(VERSION 3.12)   # CMake version check
project(CommandLineFPS)               # Create project "CommandLineFPS"
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

# Include our FindNcursesw.cmake file

# Find Ncursesw
find_package( PkgConfig REQUIRED )
pkg_check_modules(CURSES ncursesw REQUIRED)
add_compile_definitions(NCURSES_WIDECHAR)

include_directories( ${CURSES_INCLUDE_DIRS} )

# Add CommandLineFPS.cpp file of project root directory as source file
set(SOURCE_FILES main.hpp main.cpp player.h player.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(BitBorn ${SOURCE_FILES})

# Link ncursesw library
target_link_libraries( BitBorn ${CURSES_LIBRARIES} )
