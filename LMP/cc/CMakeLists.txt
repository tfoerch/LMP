add_library (lmp_cc IPCC_FSM.cpp IPCC_Impl.cpp)

target_include_directories (lmp_cc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

