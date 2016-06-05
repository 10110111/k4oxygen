include_directories (../imported/)

set(oxygenstyle_LIB_SRCS
    oxygenanimation.cpp
    oxygenhelper.cpp
    oxygenitemmodel.cpp
    oxygenshadowcache.cpp
    oxygentileset.cpp
    oxygenshadow_config.cpp
)

add_library(k4oxygenstyle SHARED ${oxygenstyle_LIB_SRCS})

target_link_libraries(k4oxygenstyle ${QT_LIBRARIES} oxygen-imported)

if ( X11_FOUND )
   target_link_libraries(k4oxygenstyle ${X11_LIBRARIES})
endif( X11_FOUND )

set_target_properties(k4oxygenstyle PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )
install(TARGETS k4oxygenstyle LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR})

# next target
#set(oxygenstyleconfig_LIB_SRCS
#    oxygenanimationconfigitem.cpp
#    oxygenbaseanimationconfigwidget.cpp
#    oxygengenericanimationconfigitem.cpp
#    oxygenshadowconfigwidget.cpp
#)

#kde4_add_ui_files(oxygenstyleconfig_LIB_SRCS
#    ui/oxygenanimationconfigitem.ui
#    ui/oxygenanimationconfigwidget.ui
#    ui/oxygengenericanimationconfigbox.ui
#    ui/oxygenshadowconfigurationui.ui
#)

#kde4_add_kcfg_files(oxygenstyleconfig_LIB_SRCS
#  oxygenactiveshadowconfiguration.kcfgc
#  oxygeninactiveshadowconfiguration.kcfgc
#)
#
#kde4_add_library(k4oxygenstyleconfig SHARED ${oxygenstyleconfig_LIB_SRCS})

#target_link_libraries(k4oxygenstyleconfig k4oxygenstyle)
#target_link_libraries(k4oxygenstyleconfig ${KDE4_KDEUI_LIBS})
#
#if ( X11_FOUND )
#   target_link_libraries(k4oxygenstyleconfig ${X11_LIBRARIES})
#endif( X11_FOUND )
#
#set_target_properties(k4oxygenstyleconfig PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )
#install(TARGETS k4oxygenstyleconfig ${INSTALL_TARGETS_DEFAULT_ARGS} )

# Note: no headers installed
