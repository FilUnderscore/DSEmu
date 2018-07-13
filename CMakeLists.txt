cmake_minimum_required(VERSION 3.6)

project(DSEmu)

# find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD, 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(lib/glfw)

FILE(GLOB_RECURSE HEADER_FILES include/*.h include/*.hpp)
include_directories(lib/glfw/include/ ${CMAKE_SOURCE_DIR} ${HEADER_FILES})

FILE(GLOB_RECURSE SOURCE_FILES src/*.c src/*.cpp)

add_definitions(-DGLFW_INCLUDE_NONE)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
