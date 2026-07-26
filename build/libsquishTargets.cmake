# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/libsquish-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${libsquish_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${libsquish_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET libsquish::libsquish)
    add_library(libsquish::libsquish INTERFACE IMPORTED)
    message(${libsquish_MESSAGE_MODE} "Conan: Target declared 'libsquish::libsquish'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/libsquish-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()