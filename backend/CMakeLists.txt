cmake_minimum_required(VERSION 3.16)

# Project configuration
project(battleship-backend VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories (relative to backend/)
include_directories(
    ui/pregame/include
    ui/ingame/include
    gameplay/board/include
    gameplay/ship/include
    gameplay/mechanics/board/include
    gameplay/mechanics/ship/include
    gameplay/mechanics/space/include
)

# Source files (relative to backend/)
set(SOURCES
    app/main.cpp
    ui/pregame/src/pregame.cpp
    ui/pregame/src/setup.cpp
    ui/ingame/src/startgame.cpp
    ui/ingame/src/ingame.cpp
    ui/ingame/src/ingameHelper.cpp
    gameplay/board/src/board.cpp
    gameplay/ship/src/ship.cpp
    gameplay/mechanics/space/src/space.cpp
    gameplay/mechanics/ship/src/ship.cpp
    gameplay/mechanics/board/src/board.cpp
)

# Create the main executable
add_executable(battleship ${SOURCES})

# Optional: Create libraries for better organization
# UI Library
set(UI_SOURCES
    ui/pregame/src/pregame.cpp
    ui/pregame/src/setup.cpp
    ui/ingame/src/startgame.cpp
    ui/ingame/src/ingame.cpp
    ui/ingame/src/ingameHelper.cpp
)

# Gameplay Library
set(GAMEPLAY_SOURCES
    gameplay/board/src/board.cpp
    gameplay/ship/src/ship.cpp
    gameplay/mechanics/space/src/space.cpp
    gameplay/mechanics/ship/src/ship.cpp
    gameplay/mechanics/board/src/board.cpp
)

# Uncomment these lines if you want to build as separate libraries
# add_library(battleship_ui STATIC ${UI_SOURCES})
# add_library(battleship_gameplay STATIC ${GAMEPLAY_SOURCES})
# target_link_libraries(battleship battleship_ui battleship_gameplay)

# Enable testing (optional)
option(BUILD_TESTS "Build test programs" OFF)
if(BUILD_TESTS)
    enable_testing()
    # Add test subdirectory if you create one later
    # add_subdirectory(tests)
endif()

# Print build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Building from backend directory")