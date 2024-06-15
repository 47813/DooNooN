cmake_minimum_required(VERSION 3.0.0)
project(doonoon VERSION 0.1.0 LANGUAGES C CXX)

# C++ standard setting
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-error=missing-braces")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add source files
add_executable(doonoon 
    main.cpp 
    CScene.cpp CScene.h 
    CSnake.cpp CSnake.h 
    CMap.cpp CMap.h 
    CMapBuilder.cpp CMapBuilder.h 
    CItems.cpp CItems.h 
    CGates.cpp CGates.h
    Mission.cpp Mission.h
)

# Link ncurses library
target_link_libraries(doonoon ${CURSES_LIBRARIES})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
