# Add executable called "LMP_T" that is built from the source files
include_directories ("${PROJECT_SOURCE_DIR}/cc/test")

find_package( Boost REQUIRED COMPONENTS unit_test_framework program_options system chrono thread )

enable_testing()

add_executable (CCUnitTest_T CCUnitTest.cpp Test_Wait.cpp Test_IPCC_Observer.cpp Test_IPCC_Msg_Receiver.cpp Test_NeighborDiscoveredCheckFtor.cpp Test_EventCallbackCalledCheckFtor.cpp Test_NoTimeoutScheduledCheckFtor.cpp)

# add_boost_test(CCUnitTest_T
# SOURCES CCUnitTest.cpp Test_Wait.cpp Test_IPCC_Observer.cpp Test_IPCC_Msg_Receiver.cpp Test_NeighborDiscoveredCheckFtor.cpp Test_EventCallbackCalledCheckFtor.cpp Test_NoTimeoutScheduledCheckFtor.cpp
# LIBRARIES lmp_cc lmp_msg lmp_obj lmp_base lmp_node lmp_neighbor ${Boost_LIBRARIES} )
#add_test(unitTest LMP_T)
#include(CppcheckTargets)
#add_cppcheck(LMP_T UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

#if(USE_IWYU)
#set_property(TARGET LMP_T PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
#endif(USE_IWYU)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
target_link_libraries (CCUnitTest_T LINK_PUBLIC lmp_cc lmp_msg lmp_obj lmp_base lmp_node lmp_neighbor ${Boost_LIBRARIES})

add_test(NAME ccUnitTests COMMAND CCUnitTest_T)


#INSTALL(TARGETS LMP_T DESTINATION bin)
