# Require at least CMake 3.20 for this project.
cmake_minimum_required(VERSION 3.20)
# Declare the project name and that it uses C++.
project(Plato LANGUAGES CXX)

# Build all targets with the C++20 language standard.
set(CMAKE_CXX_STANDARD 20)
# Enforce C++20 strictly (do not silently fall back).
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable compiler-specific language extensions for portability.
set(CMAKE_CXX_EXTENSIONS OFF)

# Locate pkg-config so we can query system-installed libraries.
find_package(PkgConfig REQUIRED)
# Import gtkmm-4.0 settings as a CMake target named PkgConfig::GTKMM.
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

# Collect all .cpp files under src/ (auto-updates when files are added/removed).
file(GLOB SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# Define the final executable target named "plato" from discovered sources.
add_executable(plato ${SRC_FILES})

# Link the executable against gtkmm and its transitive dependencies.
target_link_libraries(plato PRIVATE PkgConfig::GTKMM)
