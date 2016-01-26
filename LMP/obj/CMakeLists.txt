
add_library (lmp_obj SHARED ObjectHeader.cpp HelloConfigData.cpp)

add_cppcheck(lmp_obj UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

if(USE_IWYU)
set_property(TARGET lmp_obj PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif(USE_IWYU)

target_include_directories (lmp_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

INSTALL(TARGETS lmp_obj DESTINATION lib)
