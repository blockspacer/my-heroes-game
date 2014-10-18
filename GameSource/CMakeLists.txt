cmake_minimum_required (VERSION 2.6)

# Maps to Visual Studio solution file (Tutorial.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project (HeroesGame)

get_filename_component ( GAME_SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )

# 3rd party libraries
set(LIBRARIES_DIR "${GAME_SOURCE_ROOT}/Libraries/")
set(RESOURCES_DIR "${GAME_SOURCE_ROOT}/Resources/")

# SDL
set(SDL2_DIR "${LIBRARIES_DIR}/SDL2/")
set(SDL2_ROOT "${SDL2_DIR}/SDL2-devel-2.0.3-VC/")
set(SDL2_ttf_ROOT "${SDL2_DIR}/SDL2_ttf-devel-2.0.12-VC/")
set(SDL2_image_ROOT "${SDL2_DIR}/SDL2_image-2.0.0/")

# Box2D
set(BOX2D_DIR "${LIBRARIES_DIR}/Box2D/")
set(BOX2D_ROOT "${BOX2D_DIR}/Box2D_v2.3.0/")

# put all libs together
set(LIBS "${LIBS}" "${SDL2_ROOT}/SDL2-2.0.3/lib/x86/SDL2.lib" "${SDL2_ROOT}/SDL2-2.0.3/lib/x86/SDL2main.lib"
                   "${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.lib"
                   "${SDL2_image_ROOT}/lib/x86/SDL2_image.lib"
                   "${BOX2D_ROOT}/Box2D/Build/vs2012/bin/Debug/Box2D.lib" 
                   "${BOX2D_ROOT}/Box2D/Build/vs2012/bin/Debug/FreeGLUT.lib"
                   "${BOX2D_ROOT}/Box2D/Build/vs2012/bin/Debug/GLUI.lib"
                    )
set(FONT_DIR "${RESOURCES_DIR}/Fonts/")

add_subdirectory( Heroes )

#INCLUDE("${PROJECT_CMAKE_DIR}/macros/headless_setup.cmake")

#set(CMAKE_INCLUDE_PATH "${BUILDY_BITS_ROOT}/LibUV/include/" )

#includes directories for whole project
#include_directories(SYSTEM "${ACTOR_CONTAINER_ROOT}/3rdParty/DHCore/" )
#include_directories(SYSTEM "/usr/include" "${BUILDY_BITS_ROOT}/LibUV/include")

