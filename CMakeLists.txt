cmake_minimum_required(VERSION 3.21)

project("PVN"
        LANGUAGES CXX)

# Find all needed libraries
include(cmake/Modules.cmake)
foreach(library IN LISTS MODULES)
    find_package(${library} REQUIRED)
endforeach()

foreach(library IN LISTS QT_COMPONENTS)
    find_package(Qt6 COMPONENTS ${library} REQUIRED)
    string(TOLOWER "${library}" library_lower)
    if (library_lower STREQUAL "quick")
        set(${PROJECT_NAME}_QT_QUICK ON)
    endif()
endforeach()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
foreach(library IN LISTS BOOST_COMPONENTS)
    find_package(Boost COMPONENTS ${library} REQUIRED)
endforeach()

# Setup
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

qt_standard_project_setup()

# Model project dependencies
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

include(cmake/StandardSettings.cmake)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (UNIX)
    add_compile_options("$<$<CONFIG:DEBUG>:-D_DEBUG>")    #this will allow to use same _DEBUG macro available in both Unix as well as Windows - MSCV environment. Easy to put Debug specific code
endif (UNIX)

# Setup alternative names
if(${PROJECT_NAME}_USE_ALT_NAMES)
    string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)
    string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)
else()
    set(PROJECT_NAME_LOWERCASE ${PROJECT_NAME})
    set(PROJECT_NAME_UPPERCASE ${PROJECT_NAME})
endif()

# Prevent building in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n")
endif()

# Find all headers and implementation files
include(cmake/Sources.cmake)

# Create library/application, setup header and source files
if (APPLE)
    # Check for icon
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.icns")
        qt_add_executable("${PROJECT_NAME}_Editor" MACOSX_BUNDLE ${EDITOR_SOURCE_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.icns")
        qt_add_executable("${PROJECT_NAME}_Engine" MACOSX_BUNDLE ${ENGINE_SOURCE_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.icns")
    else()
        qt_add_executable("${PROJECT_NAME}_Editor" MACOSX_BUNDLE ${EDITOR_SOURCE_FILES})
        qt_add_executable("${PROJECT_NAME}_Engine" MACOSX_BUNDLE ${ENGINE_SOURCE_FILES})
    endif()
elseif(WIN32)
    # Check for icon
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.rc" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.ico")
        qt_add_executable("${PROJECT_NAME}_Editor" WIN32 ${EDITOR_SOURCE_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.rc")
        qt_add_executable("${PROJECT_NAME}_Engine" WIN32 ${ENGINE_SOURCE_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.rc")
    else()
        qt_add_executable("${PROJECT_NAME}_Editor" WIN32 ${EDITOR_SOURCE_FILES})
        qt_add_executable("${PROJECT_NAME}_Engine" WIN32 ${ENGINE_SOURCE_FILES})
    endif()
else()
    # Icons added at deployment
    qt_add_executable("${PROJECT_NAME}_Editor" ${EDITOR_SOURCE_FILES})
    qt_add_executable("${PROJECT_NAME}_Engine" ${ENGINE_SOURCE_FILES})
endif()

qt_add_library("${PROJECT_NAME}_Library" STATIC ${LIBRARY_SOURCE_FILES})
qt_add_library("${PROJECT_NAME}_Editor_TestLib" STATIC ${EDITOR_SOURCE_FILES})
qt_add_library("${PROJECT_NAME}_Engine_TestLib" STATIC ${ENGINE_SOURCE_FILES})

set_target_properties(${PROJECT_NAME}_Editor_TestLib
                          PROPERTIES
                          ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                          LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                          OUTPUT_NAME ${PROJECT_NAME}_Editor)

set_target_properties(${PROJECT_NAME}_Engine_TestLib
                          PROPERTIES
                          ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                          LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                          OUTPUT_NAME ${PROJECT_NAME}_Engine)

target_compile_features("${PROJECT_NAME}_Editor" PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
target_compile_features("${PROJECT_NAME}_Engine" PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
target_compile_features("${PROJECT_NAME}_Library" PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
target_compile_features("${PROJECT_NAME}_Editor_TestLib" PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
target_compile_features("${PROJECT_NAME}_Engine_TestLib" PUBLIC cxx_std_${CMAKE_CXX_STANDARD})

set_target_properties("${PROJECT_NAME}_Library"
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                      OUTPUT_NAME "pvnlib")

set_target_properties("${PROJECT_NAME}_Editor"
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")

set_target_properties("${PROJECT_NAME}_Engine"
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")

# Set the project standard and warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME}_Editor)
set_project_warnings(${PROJECT_NAME}_Library)
set_project_warnings(${PROJECT_NAME}_Engine)

# Allow usage of header files in the `src` directory, but only for utilities
target_include_directories(${PROJECT_NAME}_Editor
                           PUBLIC
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           ${CMAKE_INCLUDE_PATH} 
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME}_Library
                           PUBLIC
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           ${CMAKE_INCLUDE_PATH} 
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME}_Engine
                           PUBLIC
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           ${CMAKE_INCLUDE_PATH} 
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME}_Editor_TestLib
                           PUBLIC
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           ${CMAKE_INCLUDE_PATH} 
                           ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${PROJECT_NAME}_Engine_TestLib
                           PUBLIC
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           ${CMAKE_INCLUDE_PATH} 
                           ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_directories(${PROJECT_NAME}_Editor_TestLib
                        PRIVATE
                        ${CMAKE_LIBRARY_PATH})

target_link_directories(${PROJECT_NAME}_Engine_TestLib
                        PRIVATE
                        ${CMAKE_LIBRARY_PATH})

target_link_directories(${PROJECT_NAME}_Editor
                        PRIVATE
                        ${CMAKE_LIBRARY_PATH})

target_link_directories(${PROJECT_NAME}_Library
                        PRIVATE
                        ${CMAKE_LIBRARY_PATH})

target_link_directories(${PROJECT_NAME}_Engine
                        PRIVATE
                        ${CMAKE_LIBRARY_PATH})

# Link libraries
foreach(library IN LISTS MODULES)
    target_link_libraries(${PROJECT_NAME}_Library PRIVATE ${library})
    target_link_libraries(${PROJECT_NAME}_Editor PRIVATE ${library})
    target_link_libraries(${PROJECT_NAME}_Engine PRIVATE ${library})
    target_link_libraries(${PROJECT_NAME}_Editor_TestLib PRIVATE ${library})
    target_link_libraries(${PROJECT_NAME}_Engine_TestLib PRIVATE ${library})
endforeach()

# Link Qt libraries
foreach(library IN LISTS QT_COMPONENTS)
    target_link_libraries(${PROJECT_NAME}_Library PRIVATE Qt6::${library})
    target_link_libraries(${PROJECT_NAME}_Editor PRIVATE Qt6::${library})
    target_link_libraries(${PROJECT_NAME}_Engine PRIVATE Qt6::${library})
    target_link_libraries(${PROJECT_NAME}_Editor_TestLib PRIVATE Qt6::${library})
    target_link_libraries(${PROJECT_NAME}_Engine_TestLib PRIVATE Qt6::${library})
endforeach()

foreach(library IN LISTS BOOST_COMPONENTS)
    target_link_libraries(${PROJECT_NAME}_Library PRIVATE Boost::${library})
    target_link_libraries(${PROJECT_NAME}_Editor PRIVATE Boost::${library})
    target_link_libraries(${PROJECT_NAME}_Engine PRIVATE Boost::${library})
    target_link_libraries(${PROJECT_NAME}_Editor_TestLib PRIVATE Boost::${library})
    target_link_libraries(${PROJECT_NAME}_Engine_TestLib PRIVATE Boost::${library})
endforeach()

# Internal library
target_link_libraries(${PROJECT_NAME}_Editor PRIVATE ${PROJECT_NAME}_Library)
target_link_libraries(${PROJECT_NAME}_Engine PRIVATE ${PROJECT_NAME}_Library)
target_link_libraries(${PROJECT_NAME}_Editor_TestLib PRIVATE ${PROJECT_NAME}_Library)
target_link_libraries(${PROJECT_NAME}_Engine_TestLib PRIVATE ${PROJECT_NAME}_Library)

# Resources
include(cmake/Resources.cmake)
qt_add_resources(${PROJECT_NAME} "resources"
PREFIX "/resource"
FILES ${RESOURCES})

# Create code filters
 # For resource files 
source_group("Resources" FILES 
             "${CMAKE_BINARY_DIR}/.rcc/resources.qrc")
file(GLOB_RECURSE SOURCES "*.rc" "*.qrc")
foreach(SOURCE ${SOURCES})
    source_group("Resources" FILES ${SOURCE})
endforeach()
  # Resources defined in cmake/Resources.cmake
foreach(SOURCE ${RESOURCES})
    source_group("Resources" FILES ${SOURCE})
endforeach()

 # For source code
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h" "src/*.ui")
foreach(SOURCE ${SOURCES})
    get_filename_component(SOURCE_DIR "${SOURCE}" DIRECTORY)
    file(RELATIVE_PATH SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${SOURCE_DIR})
    string(REPLACE "src" "Source Files" SOURCE_PATH "${SOURCE_PATH}")
    source_group("${SOURCE_PATH}" FILES ${SOURCE})
endforeach()

 # For autogenerated by Qt ui_[name].h files for every src/*.ui file
file(GLOB_RECURSE SOURCES "src/*.ui")
foreach(SOURCE ${SOURCES})
    get_filename_component(FILE_NAME ${SOURCE} NAME_WE) # Extract file name without extension
    file(RELATIVE_PATH SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${SOURCE})
    string(REPLACE "${FILE_NAME}.ui" "" FILE_PATH "${SOURCE_PATH}" )
    source_group("Autogen/ui/${FILE_NAME}" FILES 
                 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include_Debug/${FILE_PATH}ui_${FILE_NAME}.h" 
                 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include_MinSizeRel/${FILE_PATH}ui_${FILE_NAME}.h"
                 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include_Release/${FILE_PATH}ui_${FILE_NAME}.h" 
                 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_autogen/include_RelWithDebInfo/${FILE_PATH}ui_${FILE_NAME}.h")
endforeach()

 # For autogenerated by Qt stamp files
source_group("Autogen/autouic" FILES
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_autogen/autouic_Debug.stamp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_autogen/autouic_MinSizeRel.stamp" 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_autogen/autouic_Release.stamp" 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_autogen/autouic_RelWithDebInfo.stamp")

source_group("Autogen/autouic" FILES
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_autogen/autouic_Debug.stamp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_autogen/autouic_MinSizeRel.stamp" 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_autogen/autouic_Release.stamp" 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_autogen/autouic_RelWithDebInfo.stamp")

source_group("Autogen/autouic" FILES
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Library_autogen/autouic_Debug.stamp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Library_autogen/autouic_MinSizeRel.stamp" 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Library_autogen/autouic_Release.stamp" 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Library_autogen/autouic_RelWithDebInfo.stamp")

 # For autogenerated by Qt MOC files
source_group("Autogen/moc" FILES 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_autogen/mocs_compilation_Debug.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_autogen/mocs_compilation_MinSizeRel.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_autogen/mocs_compilation_Release.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_autogen/mocs_compilation_RelWithDebInfo.cpp")

source_group("Autogen/moc" FILES 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_TestLib_autogen/mocs_compilation_Debug.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_TestLib_autogen/mocs_compilation_MinSizeRel.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_TestLib_autogen/mocs_compilation_Release.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Editor_TestLib_autogen/mocs_compilation_RelWithDebInfo.cpp")

source_group("Autogen/moc" FILES 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_autogen/mocs_compilation_Debug.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_autogen/mocs_compilation_MinSizeRel.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_autogen/mocs_compilation_Release.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_autogen/mocs_compilation_RelWithDebInfo.cpp")

source_group("Autogen/moc" FILES 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_TestLib_autogen/mocs_compilation_Debug.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_TestLib_autogen/mocs_compilation_MinSizeRel.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_TestLib_autogen/mocs_compilation_Release.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Engine_TestLib_autogen/mocs_compilation_RelWithDebInfo.cpp")

source_group("Autogen/moc" FILES 
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Library_autogen/mocs_compilation_Debug.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Library_autogen/mocs_compilation_MinSizeRel.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Library_autogen/mocs_compilation_Release.cpp"
             "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_Library_autogen/mocs_compilation_RelWithDebInfo.cpp")

source_group("CMake Rules" FILES "CMakeLists.txt")

# Provide alias to library for
add_executable(${PROJECT_NAME}_Editor::${PROJECT_NAME}_Editor ALIAS ${PROJECT_NAME}_Editor)
add_executable(${PROJECT_NAME}_Engine::${PROJECT_NAME}_Engine ALIAS ${PROJECT_NAME}_Engine)
add_library(${PROJECT_NAME}_Library::${PROJECT_NAME}_Library ALIAS ${PROJECT_NAME}_Library)

# Deployment
if(APPLE)
    set_target_properties(${PROJECT_NAME}_Editor PROPERTIES
                          MACOSX_BUNDLE TRUE)
    set_target_properties(${PROJECT_NAME}_Engine PROPERTIES
                          MACOSX_BUNDLE TRUE)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.icns")
        set(MACOSX_BUNDLE_ICON_FILE icon.icns)
        set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.icns" PROPERTIES
                                    MACOSX_PACKAGE_LOCATION "Resources")
    endif()
elseif(WIN32)
    set_target_properties(${PROJECT_NAME}_Editor PROPERTIES
                          WIN32_EXECUTABLE TRUE)
    set_target_properties(${PROJECT_NAME}_Engine PROPERTIES
                          WIN32_EXECUTABLE TRUE)
endif()

# Install target
if(APPLE)
    install(TARGETS ${PROJECT_NAME}_Editor
            CONFIGURATIONS Release
            BUNDLE DESTINATION .)
    install(TARGETS ${PROJECT_NAME}_Engine
            CONFIGURATIONS Release
            BUNDLE DESTINATION .)
    set(EXECUTABLE_PATH "./$<TARGET_FILE_NAME:${PROJECT_NAME}_Editor>.app")
    set(EXECUTABLE_PATH2 "./$<TARGET_FILE_NAME:${PROJECT_NAME}_Engine>.app")
    set(CMAKE_INSTALL_PREFIX "./install")
else()
    install(TARGETS ${PROJECT_NAME}_Editor
            CONFIGURATIONS Release
            RUNTIME DESTINATION .)
        install(TARGETS ${PROJECT_NAME}_Engine
            CONFIGURATIONS Release
            RUNTIME DESTINATION .)
    if(UNIX)
        set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/install")
    else()
        set(CMAKE_INSTALL_PREFIX "install")
    endif()
    set(EXECUTABLE_PATH "$<TARGET_FILE:${PROJECT_NAME}_Editor>")
    set(EXECUTABLE_PATH2 "$<TARGET_FILE:${PROJECT_NAME}_Engine>")
endif()

qt_generate_deploy_app_script(TARGET ${PROJECT_NAME}_Editor
                          OUTPUT_SCRIPT DEPLOY_SCRIPT)

qt_generate_deploy_app_script(TARGET ${PROJECT_NAME}_Engine
                          OUTPUT_SCRIPT DEPLOY_SCRIPT2)

install(SCRIPT ${DEPLOY_SCRIPT})
install(SCRIPT ${DEPLOY_SCRIPT2})

# Testing setup
enable_testing(true)
add_subdirectory(test)
