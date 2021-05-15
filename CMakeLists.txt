cmake_minimum_required(VERSION 3.0)
project(tracy)

find_package(ROOT REQUIRED)
find_package(ROOT COMPONENTS Core Geom GeomPainter TreePlayer MathCore MathMore Gui REQUIRED)

include(${ROOT_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/inc ${FLT_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)

set(DATA
    config.ini
  )

foreach(_data ${DATA})
    configure_file (
        ${PROJECT_SOURCE_DIR}/${_data}
        ${PROJECT_BINARY_DIR}/${_data}
        COPYONLY
    )
endforeach()

add_executable(tracy tracy.cc ${sources} ${headers})
target_link_libraries(tracy ${ROOT_LIBRARIES})
