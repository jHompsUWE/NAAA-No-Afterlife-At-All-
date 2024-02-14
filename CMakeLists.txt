cmake_minimum_required(VERSION 3.10)

project(demo)

set(CMAKE_SYSTEM_VERSION 10.0)
add_compile_definitions(_WIN32_WINNT=0x0A00)



#include(ExternalProject)
#set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
#
#ExternalProject_Add(DirectXTK
#        URL https://github.com/microsoft/DirectXTK/archive/refs/tags/apr2023.zip
#        PREFIX ${EXTERNAL_INSTALL_LOCATION}
#        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#        DOWNLOAD_EXTRACT_TIMESTAMP true
#        BUILD_COMMAND ${CMAKE_COMMAND} --build .
#)

find_package(directxtk QUIET) # QUIET or REQUIRED
if (NOT directxtk_FOUND) # If there's none, fetch and build
    include(FetchContent)
    FetchContent_Declare(
            directxtk
            GIT_REPOSITORY https://github.com/microsoft/DirectXTK.git
            GIT_TAG dec2023
    )
    fetchcontent_makeavailable(directxtk)
endif()

set(game
        Game/Game.h
        Game/TPSCamera.h
        Game/VBGO.h
        Game/VBSnail.h
        Game/VBCube.h
        Game/treebit.h
        Game/Tree.h
        Game/TextGO2D.h
        Game/TestSound.h
        Game/Terrain.h
        Game/Sound.h
        Game/Player.h
        Game/pch.h
        Game/MarchCubes.h
        Game/Loop.h
        Game/light.h

        Game/ImageGO2D.h
        Game/GPGO.h
        Game/GameObject2D.h
        Game/gameobject.h
        #Game/GameMenu.h
        Game/fileVBGO.h

        Game/Game.cpp
        Game/TPSCamera.cpp
        Game/camera.h
        Game/camera.cpp
        Game/VBGO.cpp

        Game/VBSnail.cpp
        Game/VBCube.cpp

        Game/treebit.cpp
        Game/Tree.cpp

        Game/TextGO2D.cpp
        Game/TestSound.cpp
        Game/Terrain.cpp
        Game/Sound.cpp
        Game/Player.cpp
        Game/pch.cpp
        Game/MarchCubes.cpp
        Game/Loop.cpp
        Game/light.cpp
        Game/fileVBGO.cpp
        Game/CMOGO.cpp
        Game/CMOGO.h
        Game/ImageGO2D.cpp

        Game/GPGO.cpp
        Game/GameObject2D.cpp
        Game/gameobject.cpp
)
add_executable(demo Direct3D_Win32/Main.cpp ${game})

set_target_properties(demo PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
)



#target_include_directories(demo PRIVATE ${EXTERNAL_INSTALL_LOCATION}/include)
#target_link_directories(demo PRIVATE ${EXTERNAL_INSTALL_LOCATION}/lib)
target_link_libraries(demo PRIVATE Microsoft::DirectXTK)
target_include_directories(demo PRIVATE ${DirectXTK_SOURCE_DIR}/Inc)
#add_dependencies(demo DirectXTK)

