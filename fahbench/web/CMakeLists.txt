
set(MAKE_WEB_GUI ON CACHE BOOL "Make web gui")

if(${MAKE_WEB_GUI})
add_executable(FAHBench-web WIN32
    main.cpp
    connection.cpp
    connection_manager.cpp
    mime_types.cpp
    reply.cpp
    request_handler.cpp
    request_parser.cpp
    server.cpp
    FahIcon.rc
)

add_dependencies(FAHBench-web boost)
target_link_libraries(FAHBench-web ${BOOST_WEB_LIBRARIES} pthread)
#target_link_libraries(FAHBench-gui fahbench Qt5::Widgets)

INSTALL(TARGETS FAHBench-web
        RUNTIME DESTINATION bin
)


endif()
