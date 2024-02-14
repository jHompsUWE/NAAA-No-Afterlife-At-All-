cmake_minimum_required(VERSION 3.10)

project(demo)

include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(DirectXTK
        URL https://github.com/microsoft/DirectXTK/archive/refs/tags/apr2023.zip
        PREFIX ${EXTERNAL_INSTALL_LOCATION}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
        DOWNLOAD_EXTRACT_TIMESTAMP true
        BUILD_COMMAND ${CMAKE_COMMAND} --build .
)

set(xaudio_nupkg "${CMAKE_BINARY_DIR}/xaudio2redist.nupkg")
if (NOT EXISTS "${CMAKE_BINARY_DIR}/xaudio2redist.nupkg")
    file(DOWNLOAD https://www.nuget.org/api/v2/package/Microsoft.XAudio2.Redist "${CMAKE_BINARY_DIR}/xaudio2redist.nupkg")
endif ()
if(NOT EXISTS "${CMAKE_BINARY_DIR}/external/xaudio2redist")
    file(ARCHIVE_EXTRACT INPUT "${CMAKE_BINARY_DIR}/xaudio2redist.nupkg" DESTINATION "${CMAKE_BINARY_DIR}/external/xaudio2redist")
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
        #Game/InputManager.h
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
        #Game/UIRemote.cpp
        Game/treebit.cpp
        Game/Tree.cpp
        #Game/TileGO.cpp
        #Game/TextureToTxT.cpp
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




target_include_directories(demo PRIVATE ${EXTERNAL_INSTALL_LOCATION}/include)
target_link_directories(demo PRIVATE ${EXTERNAL_INSTALL_LOCATION}/lib)
target_link_libraries(demo PRIVATE d3d11.lib d3dcompiler.lib dxgi.lib DirectXTK.lib)
add_dependencies(demo DirectXTK)

include_directories(${EXTERNAL_INSTALL_LOCATION}/xaudio2redist/build/native/include)
set(XAUDIO2REDIST_LIB_PATH "${EXTERNAL_INSTALL_LOCATION}/xaudio2redist/build/native")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(XAUDIO2REDIST_LIB_PATH "${XAUDIO2REDIST_LIB_PATH}/debug/lib")
else()
    set(XAUDIO2REDIST_LIB_PATH "${XAUDIO2REDIST_LIB_PATH}/release/lib")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
    set(XAUDIO2REDIST_LIB_PATH "${XAUDIO2REDIST_LIB_PATH}/x64")
else() # 32-bit
    set(XAUDIO2REDIST_LIB_PATH "${XAUDIO2REDIST_LIB_PATH}/x86")
endif()
link_directories(${XAUDIO2REDIST_LIB_PATH})
target_link_libraries(demo PRIVATE ${XAUDIO2REDIST_LIB_PATH}/xaudio2_9redist.lib)

set_target_properties(demo PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
)

set(XAUDIO2REDIST_DLL_PATH "${CMAKE_BINARY_DIR}/external/xaudio2redist/build/native")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(XAUDIO2REDIST_DLL_PATH "${XAUDIO2REDIST_DLL_PATH}/debug/bin")
else()
    set(XAUDIO2REDIST_DLL_PATH "${XAUDIO2REDIST_DLL_PATH}/release/bin")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit
    set(XAUDIO2REDIST_DLL_PATH "${XAUDIO2REDIST_DLL_PATH}/x64")
else() # 32-bit
    set(XAUDIO2REDIST_DLL_PATH "${XAUDIO2REDIST_DLL_PATH}/x86")
endif()

# Add a custom command to copy the XAudio2 DLL to the output directory
add_custom_command(TARGET demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${XAUDIO2REDIST_DLL_PATH}/XAudio2_9redist.dll"
        $<TARGET_FILE_DIR:demo>)