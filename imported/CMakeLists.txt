project(kstyle-oxygen-transparent)

set(oxygen_imported_SRCS
    oxygenconfig.cpp
    oxygenoption.cpp
    oxygenoptionmap.cpp
    oxygennetrootinfo.cpp
    kcolorscheme.cpp
    kcolorutils.cpp
    kcolorhelpers.cpp
    kcolorspaces.cpp
   )
add_library(oxygen-imported SHARED ${oxygen_imported_SRCS})

target_link_libraries(oxygen-imported ${QT_LIBRARIES})
if ( X11_FOUND )
   target_link_libraries(oxygen-imported ${X11_LIBRARIES})
endif( X11_FOUND )

set_target_properties(oxygen-imported PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )
install(TARGETS oxygen-imported ${INSTALL_TARGETS_DEFAULT_ARGS})
