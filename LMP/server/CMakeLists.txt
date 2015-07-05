# Add executable called "LMP_T" that is built from the source files

find_package(Boost COMPONENTS chrono system program_options)

include_directories ("${PROJECT_SOURCE_DIR}/server")

add_executable (LMPServer_T Mgt_Node.cpp Mgt_IPCC.cpp Mgt_Neighbor.cpp ServerMain.cpp)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
target_link_libraries (LMPServer_T LINK_PUBLIC lmp_cc lmp_mgtif omniORB4 omnithread ${Boost_LIBRARIES} )

