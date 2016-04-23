cmake_minimum_required (VERSION 2.6)

# Maps to Visual Studio solution file (Tutorial.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE DEBUG ) 
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG" )
endif( NOT CMAKE_BUILD_TYPE )

project (HeroesGame)

get_filename_component ( GAME_SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )

add_subdirectory( Heroes )