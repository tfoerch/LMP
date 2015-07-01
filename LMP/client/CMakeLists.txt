# Add executable called "LMP_T" that is built from the source files

find_package(Boost COMPONENTS chrono system)

include_directories ("${PROJECT_SOURCE_DIR}/client")

add_executable (LMPClient_T Mgt_Client.cpp  Mgt_NodeRegistry.cpp)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
target_link_libraries (LMPClient_T LINK_PUBLIC lmp_cc lmp_mgtif omniORB4 omnithread ${Boost_LIBRARIES} )

