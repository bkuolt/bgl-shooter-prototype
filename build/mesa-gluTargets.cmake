# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/mesa-glu-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${mesa-glu_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${mesa-glu_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET mesa-glu::mesa-glu)
    add_library(mesa-glu::mesa-glu INTERFACE IMPORTED)
    message(${mesa-glu_MESSAGE_MODE} "Conan: Target declared 'mesa-glu::mesa-glu'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/mesa-glu-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()