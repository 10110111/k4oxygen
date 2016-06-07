cmake_minimum_required(VERSION 2.8)
project(k4oxygen)

set(CMAKE_AUTOMOC ON)
if(NOT DEFINED QT_VERSION)
    set(QT_VERSION 4)
endif()
if("${QT_VERSION}" STREQUAL 5 OR "${QT_VERSION}" STREQUAL Qt5)
    message("++ Compiling style for for Qt 5")
    find_package(Qt5 5.5 REQUIRED Core DBus Gui Widgets)
    find_package(Qt5 QUIET COMPONENTS X11Extras)
    set(QT_LIBRARIES Qt5::Core Qt5::DBus Qt5::Gui Qt5::Widgets Qt5::X11Extras)
    # Re-enable deprecated QWeakPointer<QObject*>
    add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0)
    if(NOT DEFINED PLUGIN_INSTALL_DIR)
        find_package(Qt5Core)
        get_target_property(QMakeExecutable ${Qt5Core_QMAKE_EXECUTABLE} IMPORTED_LOCATION)
        execute_process(COMMAND "${QMakeExecutable}" -query QT_INSTALL_PLUGINS
                        OUTPUT_VARIABLE Qt5PluginInstallDir
                        ERROR_QUIET
                        OUTPUT_STRIP_TRAILING_WHITESPACE)
        set(PLUGIN_INSTALL_DIR "${Qt5PluginInstallDir}/styles/")
    endif()
    if (Qt5X11Extras_FOUND)
        set(X11_FOUND TRUE)
        # Re-add the define removed in Qt5
        add_definitions(-DQ_WS_X11)
    endif()
elseif("${QT_VERSION}" STREQUAL 4 OR "${QT_VERSION}" STREQUAL Qt4)
    message("++ Compiling style for for Qt 4")
    find_package(Qt4 4.8 REQUIRED QtCore QtDBus QtGui)
    include(${QT_USE_FILE})
    if(NOT DEFINED PLUGIN_INSTALL_DIR)
        set(PLUGIN_INSTALL_DIR "${QT_PLUGINS_DIR}/styles/")
    endif()
else()
    message(FATAL_ERROR "QT_VERSION must be either of 4, Qt4, 5, Qt5")
endif()

message("++ Will install Qt plugin to ${PLUGIN_INSTALL_DIR}")

set(GENERIC_LIB_VERSION 0.0.1)
set(GENERIC_LIB_SOVERSION 0)

add_definitions (${QT_DEFINITIONS})
include_directories (${QT_INCLUDES})
add_subdirectory(style)
