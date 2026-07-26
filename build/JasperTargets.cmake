# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/Jasper-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${jasper_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${Jasper_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET Jasper::Jasper)
    add_library(Jasper::Jasper INTERFACE IMPORTED)
    message(${Jasper_MESSAGE_MODE} "Conan: Target declared 'Jasper::Jasper'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/Jasper-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()