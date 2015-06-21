# CMakeLists files in this project can
# refer to the root source directory of the project as ${LMP_SOURCE_DIR} and
# to the root binary directory of the project as ${LMP_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (LMP)
include_directories ("${PROJECT_SOURCE_DIR}/base" "${PROJECT_SOURCE_DIR}/cc")

add_subdirectory (cc)
add_subdirectory (Test)

