include(B:/Dysk/Studia - private/Edge Computing/PNAMSC/build/.qt/QtDeploySupport-RelWithDebInfo.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/PVN_Engine-plugins-RelWithDebInfo.cmake" OPTIONAL)
set(__QT_DEPLOY_ALL_MODULES_FOUND_VIA_FIND_PACKAGE "ZlibPrivate;EntryPointPrivate;Core;Gui;Widgets;OpenGL;OpenGLWidgets;Network;Multimedia")

                          qt_deploy_runtime_dependencies(EXECUTABLE "B:/Dysk/Studia - private/Edge Computing/PNAMSC/build/bin/Debug/RelWithDebInfo/PVN_Engine.exe"
                          BIN_DIR .
                          VERBOSE)