include_directories (animations debug transitions . ../libs/ ../libs/imported/ ${CMAKE_BINARY_DIR}/style/)

set(oxygenstyle_LIB_SRCS
    ../libs/oxygenanimation.cpp
    ../libs/oxygenhelper.cpp
    ../libs/oxygenitemmodel.cpp
    ../libs/oxygenshadowcache.cpp
    ../libs/oxygentileset.cpp
    ../libs/oxygenshadow_config.cpp
)
set(oxygen_imported_SRCS
    ../libs/imported/oxygenconfig.cpp
    ../libs/imported/oxygenoptionmap.cpp
    ../libs/imported/oxygennetrootinfo.cpp
    ../libs/imported/kcolorscheme.cpp
    ../libs/imported/kcolorutils.cpp
    ../libs/imported/kcolorhelpers.cpp
    ../libs/imported/kcolorspaces.cpp
   )
set(k4oxygen_PART_SRCS
    animations/oxygenanimations.cpp
    animations/oxygenanimationdata.cpp
    animations/oxygenbaseengine.cpp
    animations/oxygendockseparatordata.cpp
    animations/oxygendockseparatorengine.cpp
    animations/oxygenenabledata.cpp
    animations/oxygengenericdata.cpp
    animations/oxygenheaderviewdata.cpp
    animations/oxygenheaderviewengine.cpp
    animations/oxygenmdiwindowdata.cpp
    animations/oxygenmdiwindowengine.cpp
    animations/oxygenmenubardata.cpp
    animations/oxygenmenubarengine.cpp
    animations/oxygenmenudata.cpp
    animations/oxygenmenuengine.cpp
    animations/oxygenprogressbardata.cpp
    animations/oxygenprogressbarengine.cpp
    animations/oxygenscrollbardata.cpp
    animations/oxygenscrollbarengine.cpp
    animations/oxygensliderdata.cpp
    animations/oxygensliderengine.cpp
    animations/oxygenspinboxdata.cpp
    animations/oxygenspinboxengine.cpp
    animations/oxygensplitterengine.cpp
    animations/oxygentabbardata.cpp
    animations/oxygentabbarengine.cpp
    animations/oxygentoolbardata.cpp
    animations/oxygentoolbarengine.cpp
    animations/oxygentoolboxengine.cpp
    animations/oxygenwidgetstatedata.cpp
    animations/oxygenwidgetstateengine.cpp
    debug/oxygenwidgetexplorer.cpp
    transitions/oxygencomboboxdata.cpp
    transitions/oxygencomboboxengine.cpp
    transitions/oxygenlabeldata.cpp
    transitions/oxygenlabelengine.cpp
    transitions/oxygenlineeditdata.cpp
    transitions/oxygenlineeditengine.cpp
    transitions/oxygenstackedwidgetdata.cpp
    transitions/oxygenstackedwidgetengine.cpp
    transitions/oxygentransitiondata.cpp
    transitions/oxygentransitions.cpp
    transitions/oxygentransitionwidget.cpp
    oxygenargbhelper.cpp
    oxygenblurhelper.cpp
    oxygenframeshadow.cpp
    oxygenmdiwindowshadow.cpp
    oxygenmnemonics.cpp
    oxygenpropertynames.cpp
    oxygenshadowhelper.cpp
    oxygensplitterproxy.cpp
    oxygenstyle.cpp
    oxygenstylehelper.cpp
    oxygenwindowmanager.cpp
    oxygenstyleconfigdata.cpp
)

# emulate what kde4_add_plugin would do
add_library(k4oxygen SHARED ${k4oxygen_PART_SRCS} ${oxygenstyle_LIB_SRCS} ${oxygen_imported_SRCS})
set_target_properties(k4oxygen PROPERTIES PREFIX "")

target_link_libraries(k4oxygen  ${QT_LIBRARIES})

if ( X11_FOUND )
   target_link_libraries(k4oxygen ${X11_LIBRARIES})
endif( X11_FOUND )

install(TARGETS k4oxygen LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR})
