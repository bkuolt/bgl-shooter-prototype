# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/module-GLUT-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${freeglut_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${GLUT_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET GLUT::GLUT)
    add_library(GLUT::GLUT INTERFACE IMPORTED)
    message(${GLUT_MESSAGE_MODE} "Conan: Target declared 'GLUT::GLUT'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/module-GLUT-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()