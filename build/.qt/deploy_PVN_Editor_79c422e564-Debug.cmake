include(B:/Dysk/Studia - private/Edge Computing/PNAMSC/build/.qt/QtDeploySupport-Debug.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/PVN_Editor-plugins-Debug.cmake" OPTIONAL)
set(__QT_DEPLOY_ALL_MODULES_FOUND_VIA_FIND_PACKAGE "ZlibPrivate;EntryPointPrivate;Core;Gui;Widgets;OpenGL;OpenGLWidgets;Network;Multimedia")

                          qt_deploy_runtime_dependencies(EXECUTABLE "B:/Dysk/Studia - private/Edge Computing/PNAMSC/build/bin/Debug/Debug/PVN_Editor.exe"
                          BIN_DIR .
                          VERBOSE)