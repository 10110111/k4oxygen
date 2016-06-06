include_directories (imported/)

set(oxygenstyle_LIB_SRCS
    oxygenanimation.cpp
    oxygenhelper.cpp
    oxygenitemmodel.cpp
    oxygenshadowcache.cpp
    oxygentileset.cpp
    oxygenshadow_config.cpp
)
set(oxygen_imported_SRCS
    imported/oxygenconfig.cpp
    imported/oxygenoptionmap.cpp
    imported/oxygennetrootinfo.cpp
    imported/kcolorscheme.cpp
    imported/kcolorutils.cpp
    imported/kcolorhelpers.cpp
    imported/kcolorspaces.cpp
   )

add_library(k4oxygenstyle SHARED ${oxygenstyle_LIB_SRCS} ${oxygen_imported_SRCS})

target_link_libraries(k4oxygenstyle ${QT_LIBRARIES})

if ( X11_FOUND )
   target_link_libraries(k4oxygenstyle ${X11_LIBRARIES})
endif( X11_FOUND )

set_target_properties(k4oxygenstyle PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )
install(TARGETS k4oxygenstyle LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR})
