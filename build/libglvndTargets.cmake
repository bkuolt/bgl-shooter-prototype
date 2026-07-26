# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/libglvnd-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${libglvnd_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${libglvnd_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET libglvnd::libglvnd)
    add_library(libglvnd::libglvnd INTERFACE IMPORTED)
    message(${libglvnd_MESSAGE_MODE} "Conan: Target declared 'libglvnd::libglvnd'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/libglvnd-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()