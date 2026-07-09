cmake_minimum_required(VERSION 3.16)
project(PenguinEngine VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory: place build artifacts in the project's `builds` folder
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/builds)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(WARNING "In-source build detected. Recommended: mkdir builds && cmake -S . -B builds")
endif()

# Collect all sources and headers recursively so adding files later requires no CMake change
file(GLOB_RECURSE ENGINE_SOURCES
     ${CMAKE_SOURCE_DIR}/src/*.cpp
     ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE ENGINE_HEADERS
     ${CMAKE_SOURCE_DIR}/include/*.h
     ${CMAKE_SOURCE_DIR}/include/*.hpp)

add_executable(penguin ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Include directories (project headers and third-party header folders already present)
target_include_directories(penguin PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/glad
  ${CMAKE_SOURCE_DIR}/include/GLFW
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/src/Graphics/Renderer
  ${CMAKE_SOURCE_DIR}/src/Graphics/shaders
  ${CMAKE_SOURCE_DIR}/src/window
  ${CMAKE_SOURCE_DIR}/src/gfx
)

# Try to find OpenGL (required) and optional GLFW via pkg-config or system package
find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
  target_link_libraries(penguin PRIVATE OpenGL::GL)
endif()

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
  pkg_check_modules(GLFW_PKG QUIET glfw3)
  if(GLFW_PKG_FOUND)
    target_include_directories(penguin PRIVATE ${GLFW_PKG_INCLUDE_DIRS})
    target_link_libraries(penguin PRIVATE ${GLFW_PKG_LIBRARIES})
  endif()
endif()

# If you keep a local copy of glad/GLFW as source, you can add them easily:
# add_subdirectory(third_party/glad)
# target_link_libraries(penguin PRIVATE glad)

# Group sources in IDEs for clarity
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Source Files" FILES ${ENGINE_SOURCES})
source_group(TREE ${CMAKE_SOURCE_DIR}/include PREFIX "Header Files" FILES ${ENGINE_HEADERS})

install(TARGETS penguin DESTINATION bin)

# Quick usage notes (kept as comments for convenience):
# Out-of-source build recommended:
#   mkdir builds
#   cmake -S . -B builds
#   cmake --build builds --config Release
