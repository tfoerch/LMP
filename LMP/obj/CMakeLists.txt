
add_library (lmp_obj SHARED ObjectHeader.cpp HelloConfigData.cpp ControlChannelIdData.cpp MessageIdData.cpp NodeIdData.cpp HelloData.cpp
ByteSequence.cpp ObjectClass.cpp ControlChannelIdClass.cpp LocalCCId.cpp RemoteCCId.cpp UnknownCCIdCType.cpp ControlChannelIdCTypes.cpp NodeIdClass.cpp LocalNodeId.cpp RemoteNodeId.cpp UnknownNodeIdCType.cpp MessageIdClass.cpp MessageId.cpp MessageIdAck.cpp UnknownMessageIdCType.cpp ConfigClass.cpp UnknownConfigCType.cpp HelloConfig.cpp HelloClass.cpp Hello.cpp UnknownHelloCType.cpp UnknownObjectClass.cpp)

add_cppcheck(lmp_obj UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

if(USE_IWYU)
set_property(TARGET lmp_obj PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif(USE_IWYU)

enable_testing()

add_subdirectory (test)

target_include_directories (lmp_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

INSTALL(TARGETS lmp_obj DESTINATION lib)
