
set(MAKE_WEB_GUI ON CACHE BOOL "Make web gui")

if(${MAKE_WEB_GUI})
add_executable(FAHBench-web WIN32
    web-main.cpp
    VersionHandler.cpp
    DeviceHandler.cpp
    DefaultHandler.cpp
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
target_link_libraries(FAHBench-web
    fahbench
    pthread)
#target_link_libraries(FAHBench-gui fahbench Qt5::Widgets)

INSTALL(TARGETS FAHBench-web
        RUNTIME DESTINATION bin
)

INSTALL(FILES
    app/app.js
    app/bower_components/angular/angular.js
    app/bower_components/angular-route/angular-route.js
    app/bower_components/angular-resource/angular-resource.js
    app/bower_components/bootstrap/dist/js/bootstrap.js
    app/bower_components/jquery/dist/jquery.js
    DESTINATION app/js
)

INSTALL(FILES
    app/app.css
    app/bower_components/bootstrap/dist/css/bootstrap.css
    DESTINATION app/css
)

INSTALL(FILES
    app/index.html
    DESTINATION app
)

INSTALL(DIRECTORY
    app/view1
    DESTINATION
    app
)

INSTALL(DIRECTORY
    app/view2
    DESTINATION
    app
)
    


endif()
