cmake_minimum_required(VERSION 3.0)
project(elal)

find_package(ROOT REQUIRED)

include(${ROOT_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/inc ${FLT_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)

add_executable(tracy tracy.cc ${sources} ${headers})
target_link_libraries(tracy ${ROOT_LIBRARIES})
