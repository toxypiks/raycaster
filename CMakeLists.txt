cmake_minimum_required(VERSION 3.16)
project(raycaster)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(raylib)

set(HELPER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/helper.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/helper.h
)

add_library(helper)
target_sources(helper
 PRIVATE
  ${HELPER_SOURCES}
  )

target_include_directories(helper
 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(RAYCASTMAP_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raycastmap.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/raycastmap.h
)
 
add_library(raycastmap)
target_sources(raycastmap
 PRIVATE
  ${RAYCASTMAP_SOURCES}
  )

set(RAYCASTRAY_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raycastray.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/raycastray.h
)

add_library(raycastray)
target_sources(raycastray
 PRIVATE
  ${RAYCASTRAY_SOURCES}
  )

target_include_directories(raycastray
 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(raycastray
  PUBLIC
  raycastmap
  player
)

set(PLAYER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/player.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/player.h
)
 
add_library(player)
target_sources(player
 PRIVATE
  ${PLAYER_SOURCES}
  )

target_include_directories(player
 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(player
 PUBLIC
  raycastmap
  m
)

set(DRAWING_FUNCTIONS_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/drawing_functions.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/drawing_functions.h
)
 
add_library(drawing_functions)
target_sources(drawing_functions
 PRIVATE
  ${DRAWING_FUNCTIONS_SOURCES}
  )

target_include_directories(drawing_functions
 PRIVATE
  ${raylib_INCLUDE_DIRS}
)

target_link_libraries(drawing_functions
 ${raylib_LIBRARIES}
)

set(RAYCASTER_VIDEO_CAPTURE_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raycaster_video_capture.c
  )

add_executable(raycaster_video_capture)
target_sources(raycaster_video_capture
 PRIVATE
  ${RAYCASTER_VIDEO_CAPTURE_SRC}
)

target_include_directories(raycaster_video_capture
 PRIVATE
  ${raylib_INCLUDE_DIRS}
)

target_link_libraries(raycaster_video_capture
  ${raylib_LIBRARIES}
    player
    raycastmap
    raycastray
    drawing_functions
)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating Doxygen documentation"
        VERBATIM
    )
endif()

