cmake_minimum_required(VERSION 3.0.0)

project(VengeanceHunter)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(VengeanceHunter main.c)
set(RESOURCE_FILES
    include/player.png
)

include_directories( ${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(VengeanceHunter ${SDL2_LIBRARIES})
target_link_libraries(VengeanceHunter $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
