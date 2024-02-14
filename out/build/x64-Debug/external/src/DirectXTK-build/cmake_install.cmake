# Install script for directory: C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK-build/bin/CMake/DirectXTK.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/directxtk/DirectXTK-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/directxtk/DirectXTK-targets.cmake"
         "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK-build/CMakeFiles/Export/share/directxtk/DirectXTK-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/directxtk/DirectXTK-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/directxtk/DirectXTK-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/directxtk" TYPE FILE FILES "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK-build/CMakeFiles/Export/share/directxtk/DirectXTK-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/directxtk" TYPE FILE FILES "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK-build/CMakeFiles/Export/share/directxtk/DirectXTK-targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/directxtk" TYPE FILE FILES
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/BufferHelpers.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/CommonStates.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/DDSTextureLoader.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/DirectXHelpers.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/Effects.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/GeometricPrimitive.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/GraphicsMemory.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/Model.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/PostProcess.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/PrimitiveBatch.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/ScreenGrab.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/SpriteBatch.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/SpriteFont.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/VertexTypes.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/WICTextureLoader.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/GamePad.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/Keyboard.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/Mouse.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/SimpleMath.h"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/SimpleMath.inl"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK/Inc/Audio.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/directxtk" TYPE FILE FILES
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK-build/directxtk-config.cmake"
    "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK-build/directxtk-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/out/build/x64-Debug/external/src/DirectXTK-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
