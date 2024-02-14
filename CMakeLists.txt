cmake_minimum_required(VERSION 3.10)

project(demo)

set(CMAKE_CXX_STANDARD 17) # Set the C++ standard
set(CMAKE_SYSTEM_VERSION 10.0)
add_compile_definitions(_WIN32_WINNT=0x0A00)

# Find DirectXTK or fetch and build it if not found
find_package(DirectXTK QUIET)
if (NOT DirectXTK_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            DirectXTK
            GIT_REPOSITORY https://github.com/microsoft/DirectXTK.git
            GIT_TAG dec2023
    )
    FetchContent_GetProperties(DirectXTK)
    if (NOT DirectXTK_POPULATED)
        FetchContent_Populate(DirectXTK)

        add_subdirectory(${directxtk_SOURCE_DIR} ${directxtk_BINARY_DIR})
    endif()
endif()

find_package(Bullet QUIET)
if (NOT Bullet_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            Bullet
            GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
            GIT_TAG 3.25
    )
    FetchContent_GetProperties(Bullet)
    if (NOT Bullet_POPULATED)
        FetchContent_Populate(Bullet)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${bullet_SOURCE_DIR} ${bullet_BINARY_DIR})
    endif()
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


# Add executable target
add_executable(demo Direct3D_Win32/Main.cpp ${game})

set_target_properties(demo PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
)

INCLUDE_DIRECTORIES(${BULLET_PHYSICS_SOURCE_DIR}/src)
# Link DirectXTK with your project
target_link_libraries(demo PRIVATE DirectXTK d3d11 d3dcompiler Bullet3Dynamics Bullet3Collision LinearMath)

