cmake_minimum_required(VERSION 2.8)
project(k4oxygen)

set(CMAKE_AUTOMOC ON)
find_package(Qt4 4.8 REQUIRED QtCore QtDBus QtGui)
include(${QT_USE_FILE})

if(NOT DEFINED LIBRARY_INSTALL_DIR)
    set(LIBRARY_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib)
endif()
if(NOT DEFINED PLUGIN_INSTALL_DIR)
    set(PLUGIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/plugins/styles/)
endif()

message("++ Will install Qt plugin to ${PLUGIN_INSTALL_DIR}")
message("++ Will install support libraries to ${LIBRARY_INSTALL_DIR}")

set(GENERIC_LIB_VERSION 0.0.1)
set(GENERIC_LIB_SOVERSION 0)

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
set(CMAKE_INSTALL_RPATH ${LIBRARY_INSTALL_DIR})

add_definitions (-DQT3_SUPPORT -DQT3_SUPPORT_WARNINGS)
add_definitions (${QT_DEFINITIONS})
include_directories (${QT_INCLUDES})
include_directories( libs )
add_subdirectory( libs )
#add_subdirectory( decoration )
add_subdirectory( style )
add_subdirectory(imported)
