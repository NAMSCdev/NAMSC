########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND ms-gsl_COMPONENT_NAMES Microsoft.GSL::GSL)
list(REMOVE_DUPLICATES ms-gsl_COMPONENT_NAMES)
set(ms-gsl_FIND_DEPENDENCY_NAMES "")

########### VARIABLES #######################################################################
#############################################################################################
set(ms-gsl_PACKAGE_FOLDER_RELEASE "C:/Users/LightTab2/.conan2/p/ms-gs972aa6e83ce46/p")
set(ms-gsl_BUILD_MODULES_PATHS_RELEASE )


set(ms-gsl_INCLUDE_DIRS_RELEASE "${ms-gsl_PACKAGE_FOLDER_RELEASE}/include")
set(ms-gsl_RES_DIRS_RELEASE )
set(ms-gsl_DEFINITIONS_RELEASE )
set(ms-gsl_SHARED_LINK_FLAGS_RELEASE )
set(ms-gsl_EXE_LINK_FLAGS_RELEASE )
set(ms-gsl_OBJECTS_RELEASE )
set(ms-gsl_COMPILE_DEFINITIONS_RELEASE )
set(ms-gsl_COMPILE_OPTIONS_C_RELEASE )
set(ms-gsl_COMPILE_OPTIONS_CXX_RELEASE )
set(ms-gsl_LIB_DIRS_RELEASE )
set(ms-gsl_BIN_DIRS_RELEASE )
set(ms-gsl_LIBRARY_TYPE_RELEASE UNKNOWN)
set(ms-gsl_IS_HOST_WINDOWS_RELEASE 1)
set(ms-gsl_LIBS_RELEASE )
set(ms-gsl_SYSTEM_LIBS_RELEASE )
set(ms-gsl_FRAMEWORK_DIRS_RELEASE )
set(ms-gsl_FRAMEWORKS_RELEASE )
set(ms-gsl_BUILD_DIRS_RELEASE )
set(ms-gsl_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(ms-gsl_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${ms-gsl_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${ms-gsl_COMPILE_OPTIONS_C_RELEASE}>")
set(ms-gsl_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ms-gsl_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ms-gsl_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ms-gsl_EXE_LINK_FLAGS_RELEASE}>")


set(ms-gsl_COMPONENTS_RELEASE Microsoft.GSL::GSL)
########### COMPONENT Microsoft.GSL::GSL VARIABLES ############################################

set(ms-gsl_Microsoft.GSL_GSL_INCLUDE_DIRS_RELEASE "${ms-gsl_PACKAGE_FOLDER_RELEASE}/include")
set(ms-gsl_Microsoft.GSL_GSL_LIB_DIRS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_BIN_DIRS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_LIBRARY_TYPE_RELEASE UNKNOWN)
set(ms-gsl_Microsoft.GSL_GSL_IS_HOST_WINDOWS_RELEASE 1)
set(ms-gsl_Microsoft.GSL_GSL_RES_DIRS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_DEFINITIONS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_OBJECTS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_COMPILE_DEFINITIONS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_C_RELEASE "")
set(ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_CXX_RELEASE "")
set(ms-gsl_Microsoft.GSL_GSL_LIBS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_SYSTEM_LIBS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_FRAMEWORK_DIRS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_FRAMEWORKS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_DEPENDENCIES_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_SHARED_LINK_FLAGS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_EXE_LINK_FLAGS_RELEASE )
set(ms-gsl_Microsoft.GSL_GSL_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(ms-gsl_Microsoft.GSL_GSL_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ms-gsl_Microsoft.GSL_GSL_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ms-gsl_Microsoft.GSL_GSL_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ms-gsl_Microsoft.GSL_GSL_EXE_LINK_FLAGS_RELEASE}>
)
set(ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_C_RELEASE}>")