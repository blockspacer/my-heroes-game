cmake_minimum_required (VERSION 2.6)
project( Heroes )

#copy over the zip file and unzip 3rd party libraries
file(COPY ${GAME_SOURCE_ROOT}/Libraries.zip DESTINATION ${PROJECT_BINARY_DIR} )
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_BINARY_DIR}/Libraries.zip WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
set(LIBRARIES_DIR "${PROJECT_BINARY_DIR}/Libraries/")

set(RESOURCES_DIR "${GAME_SOURCE_ROOT}/Resources/")

# SDL
set(SDL2_DIR "${LIBRARIES_DIR}/SDL2/")
set(SDL2_ROOT "${SDL2_DIR}/SDL2-devel-2.0.3-VC/")
set(SDL2_ttf_ROOT "${SDL2_DIR}/SDL2_ttf-devel-2.0.12-VC/")
set(SDL2_image_ROOT "${SDL2_DIR}/SDL2_image-2.0.0/")

# Box2D
set(BOX2D_DIR "${LIBRARIES_DIR}/Box2D/")
set(BOX2D_ROOT "${BOX2D_DIR}/Box2D_v2.3.0/")

# tinyXML
set(TINYXML2_DIR "${LIBRARIES_DIR}/TinyXML2/")
set(TINYXML2_ROOT "${TINYXML2_DIR}/tinyxml2-master/")

# LuaBindPackage
set(LUABINDPACKAGE_DIR "${LIBRARIES_DIR}/LuaBindPackage/")
set(LUA_ROOT "${LUABINDPACKAGE_DIR}/lua/")
set(LUABIND_ROOT "${LUABINDPACKAGE_DIR}/luabind/")
set(BOOST_ROOT "${LUABINDPACKAGE_DIR}/boost/")

set(FONT_DIR "${RESOURCES_DIR}/Fonts/")

# put all libs together
set(LIBS "${LIBS}" "${SDL2_ROOT}/SDL2-2.0.3/lib/x86/SDL2.lib" "${SDL2_ROOT}/SDL2-2.0.3/lib/x86/SDL2main.lib"
                   "${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.lib"
                   "${SDL2_image_ROOT}/lib/x86/SDL2_image.lib"
                   "${BOX2D_ROOT}/Box2D/Build/vs2012/bin/Debug/Box2D.lib" 
                   "${BOX2D_ROOT}/Box2D/Build/vs2012/bin/Debug/FreeGLUT.lib"
                   "${BOX2D_ROOT}/Box2D/Build/vs2012/bin/Debug/GLUI.lib"
                   "${TINYXML2_ROOT}/build/Debug/tinyxml2.lib"
                   "${LUA_ROOT}/Debug/Lua.lib"
                   "${LUABIND_ROOT}/Debug/Luabind.lib")

file ( GLOB_RECURSE
    Heroes_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
    )
    
set (
    Heroes_INCLUDES
    "${SDL2_ROOT}/SDL2-2.0.3/include/"
    "${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/include/"
    "${SDL2_image_ROOT}/include/"
    "${BOX2D_ROOT}/Box2D/"
    "${TINYXML2_ROOT}"
    "${BOOST_ROOT}/include/"
    "${LUA_ROOT}/include/"
    "${LUABIND_ROOT}/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    )
    
include_directories ( ${Heroes_INCLUDES} )

add_executable (Heroes ${Heroes_SRC} )

target_link_libraries ( Heroes ${LIBS})



# create log directory
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Logs" )

# copy resources over
message ( "Copying Resources for Game" )
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Resources" )
file(COPY ${RESOURCES_DIR} DESTINATION ${PROJECT_BINARY_DIR}/Resources)

# make debug and release folders
message ( "Moving dlls into Debug folder." )
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Debug" )
file(COPY ${SDL2_ROOT}/SDL2-2.0.3/lib/x86/SDL2.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/libfreetype-6.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/zlib1.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_image_ROOT}/lib/x86/SDL2_image.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_image_ROOT}/lib/x86/libpng16-16.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${TINYXML2_ROOT}/build/Debug/tinyxml2.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )

message ( "Moving dlls into Release folder." )
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Release" )
file(COPY ${SDL2_ROOT}/SDL2-2.0.3/lib/x86/SDL2.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/libfreetype-6.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/zlib1.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_image_ROOT}/lib/x86/SDL2_image.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_image_ROOT}/lib/x86/libpng16-16.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${TINYXML2_ROOT}/build/Debug/tinyxml2.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )