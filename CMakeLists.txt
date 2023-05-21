cmake_minimum_required(VERSION 2.8)

project(sdl-cmake)

# if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#     set(MACOSX TRUE)
# endif()
#   set(CMAKE_C_COMPILER "gcc")
#   set(CMAKE_CXX_COMPILER "g++")
#   # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
#   # cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# If on windows, run as a desktop application, not a console application.
if (WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
endif (WIN32)

add_executable(${PROJECT_NAME} src/main.c)

INCLUDE(FindPkgConfig)

if (APPLE)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
else()
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)
endif()
# PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
# PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
# cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++

link_directories(/opt/homebrew/Cellar/sdl2)

INCLUDE_DIRECTORIES(
  ${SDL2_INCLUDE_DIRS} 
  ${SDL2IMAGE_INCLUDE_DIRS} 
  ${SDL2MIXER_INCLUDE_DIRS})
  
TARGET_LINK_LIBRARIES(
  ${PROJECT_NAME} 
  ${SDL2_LIBRARIES}
  ${SDL2IMAGE_LIBRARIES} 
  ${SDL2MIXER_LIBRARIES})
