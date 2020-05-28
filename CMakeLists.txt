cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_SOURCE_DIR}/cmake/CMakeUserMakeRulesOverride.cmake")

project(Scmpoo)

if(MSVC)
  set(CMAKE_RC_FLAGS "/c 932 /l 0x0411")
elseif(MINGW)
  set(CMAKE_RC_FLAGS "--language=0411")
endif()

add_subdirectory(Scmpoo)
