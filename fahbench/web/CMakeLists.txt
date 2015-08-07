
set(MAKE_WEB_GUI ON CACHE BOOL "Make web gui")

if(${MAKE_WEB_GUI})
add_executable(FAHBench-web WIN32
    main.cpp
    FahIcon.rc
)

#target_link_libraries(FAHBench-gui fahbench Qt5::Widgets)

INSTALL(TARGETS FAHBench-web
        RUNTIME DESTINATION bin
)

# Windows requires Qt dll's to be installed alongside
# the executable.
if(${WIN32})
  # Get path to install dll's
  get_target_property(QtWidgets_location Qt5::Widgets LOCATION)
  get_target_property(QtCore_location Qt5::Core LOCATION)
  get_target_property(QtGui_location Qt5::Gui LOCATION)
  get_filename_component(Qt_DLL_ROOT "${QtCore_location}" PATH)

  INSTALL(FILES
          "${QtWidgets_location}"
          "${QtCore_location}"
          "${QtGui_location}"
          "${Qt_DLL_ROOT}/icudt53.dll"
          "${Qt_DLL_ROOT}/icuin53.dll"
          "${Qt_DLL_ROOT}/icuuc53.dll"
  DESTINATION bin)
  INSTALL(FILES
              "${Qt_DLL_ROOT}/../plugins/platforms/qwindows.dll"
              DESTINATION bin/platforms)
endif(${WIN32})

endif()
