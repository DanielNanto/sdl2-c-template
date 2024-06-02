cmake_minimum_required(VERSION 2.8)
# cmake_minimum_required(VERSION 3.27.7)

project(sdl2-c-template)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
if(WIN32)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows") 
  # set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -mwindows") 
endif()
# if (CMAKE_COMPILER_IS_GNUCC) // CMAKE_C_COMPILER_ID 
# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra")
  # set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if (MSVC)
  set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} /W4")
  # set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

add_executable(${PROJECT_NAME})
add_subdirectory(src)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)
if (APPLE)
  # link_directories(/opt/homebrew/Cellar/)
  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_mixer REQUIRED)
endif()

INCLUDE_DIRECTORIES(
  ${SDL2_INCLUDE_DIRS} 
  ${SDL2IMAGE_INCLUDE_DIRS} 
  ${SDL2MIXER_INCLUDE_DIRS})
  
TARGET_LINK_LIBRARIES(
  ${PROJECT_NAME} 
  ${SDL2_LIBRARIES}
  ${SDL2IMAGE_LIBRARIES} 
  ${SDL2MIXER_LIBRARIES})

# Lowered the minimum required version of CMake to 2.8. Check darwin 
# compatibility.
