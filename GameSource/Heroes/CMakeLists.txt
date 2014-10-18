cmake_minimum_required (VERSION 2.6)
project( Heroes )

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
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    )
    
include_directories ( ${Heroes_INCLUDES} )

add_executable (Heroes ${Heroes_SRC} )

target_link_libraries ( Heroes ${LIBS})

# make debug and release folders
message ( "Moving dlls into Debug folder." )
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Debug" )
file(COPY ${SDL2_ROOT}/SDL2-2.0.3/lib/x86/SDL2.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/libfreetype-6.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/zlib1.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_image_ROOT}/lib/x86/SDL2_image.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${SDL2_image_ROOT}/lib/x86/libpng16-16.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )

message ( "Moving dlls into Release folder." )
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/Release" )
file(COPY ${SDL2_ROOT}/SDL2-2.0.3/lib/x86/SDL2.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/libfreetype-6.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_ttf_ROOT}/SDL2_ttf-2.0.12/lib/x86/zlib1.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_image_ROOT}/lib/x86/SDL2_image.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )
file(COPY ${SDL2_image_ROOT}/lib/x86/libpng16-16.dll DESTINATION ${PROJECT_BINARY_DIR}/Release/ )

message ( "Moving the fonts into project folder, Debug and Release folders." )
file(COPY ${FONT_DIR}/Archeologicaps.ttf DESTINATION ${PROJECT_BINARY_DIR} )
file(COPY ${FONT_DIR}/Archeologicaps.ttf DESTINATION ${PROJECT_BINARY_DIR}/Debug/ )
file(COPY ${FONT_DIR}/Archeologicaps.ttf DESTINATION ${PROJECT_BINARY_DIR}/Release/ )