cmake_minimum_required (VERSION 2.6)

# Maps to Visual Studio solution file (Tutorial.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project (HeroesGame)

get_filename_component ( GAME_SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )

add_subdirectory( Heroes )