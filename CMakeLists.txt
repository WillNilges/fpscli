cmake_minimum_required(VERSION 3.12)  # CMake version check
project(BitBorn)                      # Create project "BitBorn"
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Ncursesw
find_package( PkgConfig REQUIRED )
pkg_check_modules(CURSES ncursesw REQUIRED)
pkg_check_modules(CONFIG libconfig++ REQUIRED)
add_compile_definitions(NCURSES_WIDECHAR)

include_directories( ${CURSES_INCLUDE_DIRS} )
include_directories( ${CONFIG_INCLUDE_DIRS} )

# Add project include/ directory
include_directories( include/ )

# Copy map to build directory
configure_file(res/map/walls.dat ${CMAKE_CURRENT_BINARY_DIR}/map/walls.dat COPYONLY)
configure_file(res/map/walls.cfg ${CMAKE_CURRENT_BINARY_DIR}/map/walls.cfg COPYONLY)

# Add executable target with source files listed in SOURCES variable
file(GLOB SOURCES src/*.cpp)
add_executable(BitBorn ${SOURCES})

# Link ncursesw library
target_link_libraries( BitBorn ${CURSES_LIBRARIES} ${CONFIG_LIBRARIES} )

set(CMAKE_INSTALL_DATAROOTDIR share/bitborn)

install(TARGETS BitBorn)
install(DIRECTORY res/ TYPE DATA)
