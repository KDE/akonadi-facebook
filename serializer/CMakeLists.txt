find_package(SharedMimeInfo 0.30)
set_package_properties(SharedMimeInfo PROPERTIES DESCRIPTION "shared-mime-info" URL "http://freedesktop.org/wiki/Software/shared-mime-info" TYPE REQUIRED PURPOSE "Information about filetypes")

include_directories(
    ${KDE4_INCLUDES}
    ${KDEPIMLIBS_INCLUDE_DIRS}
)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}" )


########### status item ###############

# set( akonadi_serializer_statusitem_SRCS
#   akonadi_serializer_statusitem.cpp
# )
#
# kde4_add_plugin(akonadi_serializer_statusitem ${akonadi_serializer_statusitem_SRCS})
#
# target_link_libraries(akonadi_serializer_statusitem
#               ${KDE4_AKONADI_LIBS}
#               ${QT_QTCORE_LIBRARY}
#               ${KDE4_KDECORE_LIBS}
#               kfacebook
#               ${qjson_LIBRARIES}    # for Debian
#               ${QJSON_LIBRARIES}
#               ${QJSON_LIBRARY})
#
# install(TARGETS akonadi_serializer_statusitem DESTINATION ${PLUGIN_INSTALL_DIR})
# install(FILES akonadi_serializer_statusitem.desktop DESTINATION ${DATA_INSTALL_DIR}/akonadi/plugins/serializer)
# install(FILES x-vnd.akonadi.statusitem.xml DESTINATION ${XDG_MIME_INSTALL_DIR})

########### social notification ###############

set( akonadi_serializer_socialnotification_SRCS
  akonadi_serializer_socialnotification.cpp
)

kde4_add_plugin(akonadi_serializer_socialnotification ${akonadi_serializer_socialnotification_SRCS})

target_link_libraries(akonadi_serializer_socialnotification
              ${KDE4_AKONADI_LIBS}
              ${QT_QTCORE_LIBRARY}
              ${KDE4_KDECORE_LIBS}
              kfacebook
              ${qjson_LIBRARIES}    # for Debian
              ${QJSON_LIBRARIES}
              ${QJSON_LIBRARY})

install(TARGETS akonadi_serializer_socialnotification DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES akonadi_serializer_socialnotification.desktop DESTINATION ${DATA_INSTALL_DIR}/akonadi/plugins/serializer)
install(FILES x-vnd.akonadi.socialnotification.xml DESTINATION ${XDG_MIME_INSTALL_DIR})

update_xdg_mimetypes(${XDG_MIME_INSTALL_DIR})
