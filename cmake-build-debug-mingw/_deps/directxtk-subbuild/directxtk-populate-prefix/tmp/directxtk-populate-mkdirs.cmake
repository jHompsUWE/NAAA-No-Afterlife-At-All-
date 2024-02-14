# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/cmake-build-debug-mingw/_deps/directxtk-src"
  "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/cmake-build-debug-mingw/_deps/directxtk-build"
  "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/cmake-build-debug-mingw/_deps/directxtk-subbuild/directxtk-populate-prefix"
  "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/cmake-build-debug-mingw/_deps/directxtk-subbuild/directxtk-populate-prefix/tmp"
  "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/cmake-build-debug-mingw/_deps/directxtk-subbuild/directxtk-populate-prefix/src/directxtk-populate-stamp"
  "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/cmake-build-debug-mingw/_deps/directxtk-subbuild/directxtk-populate-prefix/src"
  "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/cmake-build-debug-mingw/_deps/directxtk-subbuild/directxtk-populate-prefix/src/directxtk-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/cmake-build-debug-mingw/_deps/directxtk-subbuild/directxtk-populate-prefix/src/directxtk-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/mrmrcory/Documents/uni/c++/NAAA-No-Afterlife-At-All-/cmake-build-debug-mingw/_deps/directxtk-subbuild/directxtk-populate-prefix/src/directxtk-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
