cmake_minimum_required(VERSION 3.0.0)

project(CucCu)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(CucCu main.c)

include_directories( ${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(../include/)

target_link_libraries(CucCu ${SDL2_LIBRARIES})
target_link_libraries(CucCu $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
