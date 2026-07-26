# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/glew-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${glew_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${glew_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET GLEW::GLEW)
    add_library(GLEW::GLEW INTERFACE IMPORTED)
    message(${glew_MESSAGE_MODE} "Conan: Target declared 'GLEW::GLEW'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/glew-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()