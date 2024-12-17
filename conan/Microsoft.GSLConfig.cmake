########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(Microsoft.GSL_FIND_QUIETLY)
    set(Microsoft.GSL_MESSAGE_MODE VERBOSE)
else()
    set(Microsoft.GSL_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Microsoft.GSLTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${ms-gsl_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(Microsoft.GSL_VERSION_STRING "4.0.0")
set(Microsoft.GSL_INCLUDE_DIRS ${ms-gsl_INCLUDE_DIRS_DEBUG} )
set(Microsoft.GSL_INCLUDE_DIR ${ms-gsl_INCLUDE_DIRS_DEBUG} )
set(Microsoft.GSL_LIBRARIES ${ms-gsl_LIBRARIES_DEBUG} )
set(Microsoft.GSL_DEFINITIONS ${ms-gsl_DEFINITIONS_DEBUG} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${ms-gsl_BUILD_MODULES_PATHS_DEBUG} )
    message(${Microsoft.GSL_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


