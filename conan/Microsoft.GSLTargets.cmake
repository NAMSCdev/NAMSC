# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/Microsoft.GSL-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${ms-gsl_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${Microsoft.GSL_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET Microsoft.GSL::GSL)
    add_library(Microsoft.GSL::GSL INTERFACE IMPORTED)
    message(${Microsoft.GSL_MESSAGE_MODE} "Conan: Target declared 'Microsoft.GSL::GSL'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/Microsoft.GSL-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()