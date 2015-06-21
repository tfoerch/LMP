# Add executable called "LMP_T" that is built from the source files
include_directories ("${PROJECT_SOURCE_DIR}/Test")

add_executable (LMP_T Test_IPCC_Observer.cpp  TestMain.cpp)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
target_link_libraries (LMP_T LINK_PUBLIC lmp_cc)

