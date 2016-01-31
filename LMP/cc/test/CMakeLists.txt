# Add executable called "LMP_T" that is built from the source files
include_directories ("${PROJECT_SOURCE_DIR}/cc/test")

find_package(Boost COMPONENTS system)
#add_executable (LMP_T Test_IPCC_Observer.cpp TestMain.cpp)
enable_testing()
add_boost_test(CCUnitTest_T
               SOURCES CCUnitTest.cpp Test_Wait.cpp Test_IPCC_Observer.cpp Test_IPCC_Msg_Receiver.cpp
               LIBRARIES lmp_cc lmp_msg lmp_obj lmp_base ${Boost_LIBRARIES})
#add_test(unitTest LMP_T)
#include(CppcheckTargets)
#add_cppcheck(LMP_T UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

#if(USE_IWYU)
#set_property(TARGET LMP_T PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
#endif(USE_IWYU)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
#target_link_libraries (LMP_T LINK_PUBLIC lmp_cc)


#add_test(NAME unitTest COMMAND LMP_T --log_level=test_suite)


#INSTALL(TARGETS LMP_T DESTINATION bin)
