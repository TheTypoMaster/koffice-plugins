project( divineProportion)

SET ( divineProportionShape_SRCS
    DivineProportionPlugin.cpp
    DivineProportionShape.cpp
    DivineProportionShapeFactory.cpp
    DivineProportionTool.cpp
    DivineProportionToolFactory.cpp
    Intro.cpp
)

kde4_add_ui_files(divineProportionShape_SRCS
    Intro.ui
)

kde4_add_plugin(divineproportionshape ${divineProportionShape_SRCS})

target_link_libraries(divineproportionshape ${FLAKE_LIBS})

########### install files ###############

install( FILES divineproportionshape.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(TARGETS divineproportionshape DESTINATION ${PLUGIN_INSTALL_DIR})

#kde4_install_icons( ${DATA_INSTALL_DIR}/koffice/icons )
