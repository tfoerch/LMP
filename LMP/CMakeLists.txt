# CMakeLists files in this project can
# refer to the root source directory of the project as ${LMP_SOURCE_DIR} and
# to the root binary directory of the project as ${LMP_BINARY_DIR}.
cmake_minimum_required (VERSION 3.3)
project (lmp)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
option(USE_CLANG "build application with clang" OFF) # OFF is the default
if(USE_CLANG)
SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++-3.8")
SET (CMAKE_C_COMPILER               "/usr/bin/clang-3.8")
endif(USE_CLANG)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-std=c++11")
find_program(iwyu_path NAMES include-what-you-use iwyu)
option(USE_IWYU "build application with iwyu analysis" OFF) # OFF is the default
#find_package(cppcheck)
#include(CppcheckTargets)

include_directories ("${PROJECT_SOURCE_DIR}/base" "${PROJECT_SOURCE_DIR}/cc" "${PROJECT_BINARY_DIR}/idl")

add_subdirectory (cc)
add_subdirectory (Test)
add_subdirectory (idl)
add_subdirectory (server)
add_subdirectory (client)

enable_testing()

SET(MAJOR_VERSION "0")
SET(MINOR_VERSION "2")
SET(PATCH_VERSION "0")
 
SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "cssrobopec,libqt4-xml,libqt4-network,libqtgui4,treeupdatablereeti")
#set(CPACK_PACKAGE_DESCRIPTION "Configure UExhibitor and launch missions")
#set(CPACK_PACKAGE_CONTACT "Adrien BARRAL aba@robopec.com")
#set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/Debian/postinst")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Thomas Förch") #required
 
INCLUDE(CPack)
 
# To use this:
# make package
# sudo dpkg -i DistanceBetweenPoints-0.1.1-Linux.deb
