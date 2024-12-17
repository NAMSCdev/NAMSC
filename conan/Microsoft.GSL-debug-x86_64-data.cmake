########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND ms-gsl_COMPONENT_NAMES Microsoft.GSL::GSL)
list(REMOVE_DUPLICATES ms-gsl_COMPONENT_NAMES)
set(ms-gsl_FIND_DEPENDENCY_NAMES "")

########### VARIABLES #######################################################################
#############################################################################################
set(ms-gsl_PACKAGE_FOLDER_DEBUG "C:/Users/LightTab2/.conan2/p/ms-gs972aa6e83ce46/p")
set(ms-gsl_BUILD_MODULES_PATHS_DEBUG )


set(ms-gsl_INCLUDE_DIRS_DEBUG "${ms-gsl_PACKAGE_FOLDER_DEBUG}/include")
set(ms-gsl_RES_DIRS_DEBUG )
set(ms-gsl_DEFINITIONS_DEBUG )
set(ms-gsl_SHARED_LINK_FLAGS_DEBUG )
set(ms-gsl_EXE_LINK_FLAGS_DEBUG )
set(ms-gsl_OBJECTS_DEBUG )
set(ms-gsl_COMPILE_DEFINITIONS_DEBUG )
set(ms-gsl_COMPILE_OPTIONS_C_DEBUG )
set(ms-gsl_COMPILE_OPTIONS_CXX_DEBUG )
set(ms-gsl_LIB_DIRS_DEBUG )
set(ms-gsl_BIN_DIRS_DEBUG )
set(ms-gsl_LIBRARY_TYPE_DEBUG UNKNOWN)
set(ms-gsl_IS_HOST_WINDOWS_DEBUG 1)
set(ms-gsl_LIBS_DEBUG )
set(ms-gsl_SYSTEM_LIBS_DEBUG )
set(ms-gsl_FRAMEWORK_DIRS_DEBUG )
set(ms-gsl_FRAMEWORKS_DEBUG )
set(ms-gsl_BUILD_DIRS_DEBUG )
set(ms-gsl_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(ms-gsl_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ms-gsl_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ms-gsl_COMPILE_OPTIONS_C_DEBUG}>")
set(ms-gsl_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ms-gsl_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ms-gsl_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ms-gsl_EXE_LINK_FLAGS_DEBUG}>")


set(ms-gsl_COMPONENTS_DEBUG Microsoft.GSL::GSL)
########### COMPONENT Microsoft.GSL::GSL VARIABLES ############################################

set(ms-gsl_Microsoft.GSL_GSL_INCLUDE_DIRS_DEBUG "${ms-gsl_PACKAGE_FOLDER_DEBUG}/include")
set(ms-gsl_Microsoft.GSL_GSL_LIB_DIRS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_BIN_DIRS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_LIBRARY_TYPE_DEBUG UNKNOWN)
set(ms-gsl_Microsoft.GSL_GSL_IS_HOST_WINDOWS_DEBUG 1)
set(ms-gsl_Microsoft.GSL_GSL_RES_DIRS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_DEFINITIONS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_OBJECTS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_COMPILE_DEFINITIONS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_C_DEBUG "")
set(ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_CXX_DEBUG "")
set(ms-gsl_Microsoft.GSL_GSL_LIBS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_SYSTEM_LIBS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_FRAMEWORK_DIRS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_FRAMEWORKS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_DEPENDENCIES_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_SHARED_LINK_FLAGS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_EXE_LINK_FLAGS_DEBUG )
set(ms-gsl_Microsoft.GSL_GSL_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(ms-gsl_Microsoft.GSL_GSL_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ms-gsl_Microsoft.GSL_GSL_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ms-gsl_Microsoft.GSL_GSL_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ms-gsl_Microsoft.GSL_GSL_EXE_LINK_FLAGS_DEBUG}>
)
set(ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ms-gsl_Microsoft.GSL_GSL_COMPILE_OPTIONS_C_DEBUG}>")