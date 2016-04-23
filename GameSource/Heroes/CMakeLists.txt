cmake_minimum_required (VERSION 2.6)
project( Heroes )

#copy over the zip file and unzip 3rd party libraries
message(STATUS "Copying library dependencies into build directories" ...)
file(COPY ${GAME_SOURCE_ROOT}/Libraries.zip DESTINATION ${PROJECT_BINARY_DIR} )
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${PROJECT_BINARY_DIR}/Libraries.zip WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
set(LIBRARIES_DIR "${PROJECT_BINARY_DIR}/Libraries")

message(STATUS "Setting directory variables" ...)
set(RESOURCES_DIR "${GAME_SOURCE_ROOT}/Resources/")

# SDL
set(SDL2_DIR "${LIBRARIES_DIR}/SDL2")
set(SDL2_ROOT "${SDL2_DIR}/SDL2-2.0.4")
set(SDL2_ttf_ROOT "${SDL2_DIR}/SDL2_ttf-2.0.14")
set(SDL2_image_ROOT "${SDL2_DIR}/SDL2_image-2.0.1")

# Box2D
set(BOX2D_DIR "${LIBRARIES_DIR}/Box2D")
set(BOX2D_ROOT "${BOX2D_DIR}/Box2D_v2.3.1")

# tinyXML
set(TINYXML2_DIR "${LIBRARIES_DIR}/TinyXML2")
set(TINYXML2_ROOT "${TINYXML2_DIR}")

# LuaBindPackage
set(LUABINDPACKAGE_DIR "${LIBRARIES_DIR}/LuaBindPackage")
set(LUA_ROOT "${LUABINDPACKAGE_DIR}/Lua")
set(LUABIND_ROOT "${LUABINDPACKAGE_DIR}/LuaBind")
set(BOOST_ROOT "${LUABINDPACKAGE_DIR}/Boost")

set(FONT_DIR "${RESOURCES_DIR}/Fonts")

# put all libs together
message(STATUS "Adding .lib files" ...)
if(CMAKE_BUILD_TYPE MATCHES DEBUG)

    message(STATUS "Adding .lib files for Debug" ...)
    set(LIBS "${LIBS}" "${SDL2_ROOT}/lib/SDL2.lib" "${SDL2_ROOT}/lib/SDL2main.lib" "${SDL2_ROOT}/lib/_SDL2main.lib"
                       "${SDL2_ttf_ROOT}/lib/x86/SDL2_ttf.lib"
                       "${SDL2_image_ROOT}/lib/x86/SDL2_image.lib"
                       "${BOX2D_ROOT}/vs2015/x32/Debug/Box2D.lib" 
                       "${BOX2D_ROOT}/vs2015/x32/Debug/glew.lib"
                       "${BOX2D_ROOT}/vs2015/x32/Debug/glfw.lib"
                       "${TINYXML2_ROOT}/lib/x86/Debug/tinyxml2.lib"
                       "${LUA_ROOT}/vs2015/x86/Debug/Lua.lib"
                       "${LUABIND_ROOT}/vs2015/x86/Debug/LuaBind.lib")

else(CMAKE_BUILD_TYPE MATCHES DEBUUG)
    message(FATAL_ERROR "Unhandled Configuration Type ${CMAKE_BUILD_TYPE}" ...)
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

message(STATUS "Adding include(s) and source code" ...)
file ( GLOB_RECURSE
    Heroes_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
    )
    
message(STATUS "Adding library includes.")
set (
    Heroes_INCLUDES
    "${SDL2_ROOT}/include/SDL2"
    "${SDL2_ttf_ROOT}/include"
    "${SDL2_image_ROOT}/include"
    "${BOX2D_ROOT}/include"
    "${TINYXML2_ROOT}/include"
    "${BOOST_ROOT}/include"
    "${LUA_ROOT}/include"
    "${LUABIND_ROOT}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )
    
include_directories ( ${Heroes_INCLUDES} )

message(STATUS "Creating solution and linking library dependencies" ...)
add_executable (Heroes ${Heroes_SRC} )
target_link_libraries ( Heroes ${LIBS})



# create log directory
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Logs" )

# copy resources over
message(STATUS "Copying .dll(s) into build directories" ...)
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Resources" )
file(COPY ${RESOURCES_DIR} DESTINATION ${PROJECT_BINARY_DIR}/Resources)

# make debug folder
if(CMAKE_BUILD_TYPE MATCHES DEBUG)

    message (STATUS "Moving .dll(s) into Debug folder" ...)
    file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Debug" )
    file(COPY ${SDL2_ROOT}/lib/SDL2.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
    file(COPY ${SDL2_ttf_ROOT}/lib/x86/libfreetype-6.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
    file(COPY ${SDL2_ttf_ROOT}/lib/x86/SDL2_ttf.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
    file(COPY ${SDL2_ttf_ROOT}/lib/x86/zlib1.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
    file(COPY ${SDL2_image_ROOT}/lib/x86/SDL2_image.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
    file(COPY ${SDL2_image_ROOT}/lib/x86/libpng16-16.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
    file(COPY ${TINYXML2_ROOT}/lib/x86/Debug/tinyxml2.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )

else(CMAKE_BUILD_TYPE MATCHES DEBUUG)
    message(FATAL_ERROR "Unhandled Configuration Type ${CMAKE_BUILD_TYPE}" ...)
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)