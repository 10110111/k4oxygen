project(oxygen-transparent)

find_package (KDE4 REQUIRED)
include (KDE4Defaults)
include (MacroLibrary)

find_package(KDE4Workspace 4.9.80 REQUIRED)

set(CMAKE_AUTOMOC ON)
find_package(Qt4 4.8 REQUIRED QtCore QtDBus QtGui)
include(${QT_USE_FILE})

add_definitions (-DQT3_SUPPORT -DQT3_SUPPORT_WARNINGS)
add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${KDE4_INCLUDES} ${KDE4WORKSPACE_INCLUDE_DIR})
include_directories( libs )
add_subdirectory( libs )
#add_subdirectory( decoration )
add_subdirectory( style )
add_subdirectory(imported)
