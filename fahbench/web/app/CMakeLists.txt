INSTALL(FILES
    app.js
    bower_components/angular/angular.js
    bower_components/angular-route/angular-route.js
    bower_components/angular-resource/angular-resource.js
    bower_components/bootstrap/dist/js/bootstrap.js
    bower_components/jquery/dist/jquery.js
    DESTINATION app/js
)

INSTALL(FILES
    app.css
    bower_components/bootstrap/dist/css/bootstrap.css
    DESTINATION app/css
)

INSTALL(FILES
    index.html
    DESTINATION app
)

INSTALL(DIRECTORY
    view1
    DESTINATION
    app
)

INSTALL(DIRECTORY
    view2
    DESTINATION
    app
)