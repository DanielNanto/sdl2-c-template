cmake_minimum_required(VERSION 2.8)

project(sdl2-c-template)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
if(WIN32)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows") 
endif()
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()
if (MSVC)
  set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} /W4")
endif()

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

if (APPLE)
  link_directories(/opt/homebrew/opt/sdl2/lib/)
  link_directories(/opt/homebrew/opt/sdl2_image/lib/)
  link_directories(/opt/homebrew/opt/sdl2_mixer/lib/)
  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_mixer REQUIRED)
endif()

INCLUDE_DIRECTORIES(
  ${SDL2_INCLUDE_DIRS} 
  ${SDL2IMAGE_INCLUDE_DIRS} 
  ${SDL2MIXER_INCLUDE_DIRS})

add_executable(${PROJECT_NAME})
add_subdirectory(src)

TARGET_LINK_LIBRARIES(
  ${PROJECT_NAME} 
  ${SDL2_LIBRARIES}
  ${SDL2IMAGE_LIBRARIES} 
  ${SDL2MIXER_LIBRARIES})
