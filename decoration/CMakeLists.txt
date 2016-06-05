########### add version number into compilation defines
add_definitions ( -DAPP_VERSION=\\\"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}\\\")
add_subdirectory( config )

########### next target ###############
set(kwin_k4oxygen_SRCS
     oxygenbutton.cpp
     oxygenclient.cpp
     oxygenclientgroupitemdata.cpp
     oxygendecohelper.cpp
     oxygenexceptionlist.cpp
     oxygenfactory.cpp
     oxygensizegrip.cpp
     oxygentitleanimationdata.cpp
  )

kde4_add_kcfg_files(kwin_k4oxygen_SRCS oxygenconfiguration.kcfgc )

kde4_add_plugin(kwin3_k4oxygen ${kwin_k4oxygen_SRCS})
target_link_libraries(
    kwin3_k4oxygen
    ${KDE4_KDEUI_LIBS}
    ${X11_X11_LIB}
    ${X11_Xrender_LIB}
    ${KDE4WORKSPACE_KDECORATIONS_LIBS}
    k4oxygenstyle
  )

install(TARGETS kwin3_k4oxygen  DESTINATION ${PLUGIN_INSTALL_DIR} )

########### install files ###############
install( FILES k4oxygenclient.desktop  DESTINATION  ${DATA_INSTALL_DIR}/kwin/ )

