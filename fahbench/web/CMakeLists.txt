
set(MAKE_WEB_GUI ON CACHE BOOL "Make web gui")

if(${MAKE_WEB_GUI})
add_executable(FAHBench-web WIN32
    web-main.cpp
    VersionHandler.cpp
    DeviceHandler.cpp
    DefaultHandler.cpp
    SimulationHandler.cpp
    request_handler.cpp
    
    # Server
    server/connection.cpp
    server/connection_manager.cpp
    server/mime_types.cpp
    server/reply.cpp
    server/request_parser.cpp
    server/server.cpp
    
    # Icon
    FahIcon.rc
)

add_dependencies(FAHBench-web boost)
target_link_libraries(FAHBench-web
    fahbench
    pthread
)


INSTALL(TARGETS FAHBench-web
        RUNTIME DESTINATION bin
)

add_subdirectory(app)
    


endif()
