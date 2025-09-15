#!/bin/bash

# Build script for battleship-cpp backend
# This script provides convenient commands for building and running the backend project

set -e  # Exit on any error

BACKEND_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$BACKEND_DIR/build"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

print_usage() {
    echo -e "${BLUE}Battleship Backend Build Script${NC}"
    echo "Usage: $0 [command]"
    echo ""
    echo "Commands:"
    echo "  build, b       - Build the backend (Release mode)"
    echo "  debug, d       - Build in Debug mode"
    echo "  run, r         - Build and run the backend"
    echo "  clean, c       - Clean build files"
    echo "  rebuild, rb    - Clean and build"
    echo "  install, i     - Install dependencies (if any)"
    echo "  help, h        - Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 build      # Build the backend"
    echo "  $0 run        # Build and run"
    echo "  $0 debug      # Build with debug symbols"
    echo ""
    echo "Note: This script should be run from the backend/ directory"
}

create_build_dir() {
    if [ ! -d "$BUILD_DIR" ]; then
        echo -e "${YELLOW}Creating build directory...${NC}"
        mkdir -p "$BUILD_DIR"
    fi
}

build_project() {
    local build_type=${1:-Release}
    echo -e "${BLUE}Building backend in $build_type mode...${NC}"
    
    # Ensure we're in the backend directory
    cd "$BACKEND_DIR"
    
    create_build_dir
    cd "$BUILD_DIR"
    
    cmake -DCMAKE_BUILD_TYPE=$build_type ..
    cmake --build . -j$(nproc)
    
    echo -e "${GREEN}Backend build completed successfully!${NC}"
}

run_project() {
    build_project Release
    echo -e "${BLUE}Running battleship backend...${NC}"
    
    if [ -f "$BUILD_DIR/bin/battleship" ]; then
        "$BUILD_DIR/bin/battleship"
    else
        echo -e "${RED}Error: battleship executable not found!${NC}"
        exit 1
    fi
}

clean_project() {
    echo -e "${YELLOW}Cleaning backend build files...${NC}"
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        echo -e "${GREEN}Clean completed!${NC}"
    else
        echo -e "${YELLOW}No build directory to clean.${NC}"
    fi
}

# Check if we're in the correct directory
if [[ ! -f "$BACKEND_DIR/CMakeLists.txt" ]]; then
    echo -e "${RED}Error: This script should be run from the backend/ directory${NC}"
    echo -e "${YELLOW}Current directory: $(pwd)${NC}"
    echo -e "${YELLOW}Expected directory: $BACKEND_DIR${NC}"
    exit 1
fi

# Main script logic
case "${1:-build}" in
    "build"|"b")
        build_project Release
        ;;
    "debug"|"d")
        build_project Debug
        ;;
    "run"|"r")
        run_project
        ;;
    "clean"|"c")
        clean_project
        ;;
    "rebuild"|"rb")
        clean_project
        build_project Release
        ;;
    "install"|"i")
        echo -e "${YELLOW}No backend dependencies to install currently.${NC}"
        echo -e "${BLUE}If you need to install CMake, run:${NC}"
        echo "  sudo apt update && sudo apt install cmake build-essential"
        ;;
    "help"|"h"|"--help")
        print_usage
        ;;
    *)
        echo -e "${RED}Unknown command: $1${NC}"
        print_usage
        exit 1
        ;;
esac