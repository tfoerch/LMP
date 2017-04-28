# Add executable called "LMP_T" that is built from the source files

find_package(Boost COMPONENTS chrono system program_options)

include_directories ("${PROJECT_SOURCE_DIR}/server")

add_executable (LMPServer_T Mgt_Node.cpp Mgt_NodeApplProxy.cpp Mgt_UDPMsgReceiveIFProxy.cpp Mgt_IPCC.cpp Mgt_Neighbor.cpp Mgt_NetIF.cpp Mgt_NetworkIFProxy.cpp IPCCObserverProxy.cpp ServerMain.cpp)

add_cppcheck(LMPServer_T UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

if(USE_IWYU)
set_property(TARGET LMPServer_T PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif(USE_IWYU)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
target_link_libraries (LMPServer_T LINK_PUBLIC lmp_node lmp_neighbor lmp_cc lmp_msg lmp_obj lmp_base lmp_mgtif omniORB4 omnithread ${Boost_LIBRARIES} )
INSTALL(TARGETS LMPServer_T DESTINATION bin)
