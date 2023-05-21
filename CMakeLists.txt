cmake_minimum_required(VERSION 2.8)

project(sdl-cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# If on windows, run as a desktop application, not a console application.
if (WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows") # redirect printf
endif (WIN32)

add_executable(${PROJECT_NAME} src/main.c)

INCLUDE(FindPkgConfig)

# link_directories(/opt/homebrew/Cellar/)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)
if (APPLE)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
endif()
# else()

INCLUDE_DIRECTORIES(
  ${SDL2_INCLUDE_DIRS} 
  ${SDL2IMAGE_INCLUDE_DIRS} 
  ${SDL2MIXER_INCLUDE_DIRS})
  
TARGET_LINK_LIBRARIES(
  ${PROJECT_NAME} 
  ${SDL2_LIBRARIES}
  ${SDL2IMAGE_LIBRARIES} 
  ${SDL2MIXER_LIBRARIES})
