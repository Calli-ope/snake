cmake_minimum_required(VERSION 3.16)
project(Snake LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Snake src/main.cpp
        src/headers/State.h
        src/headers/StateController.h
        src/StateController.cpp
        src/AssetManager.cpp
        src/headers/AssetManager.h
        src/Game.cpp
        src/headers/Game.h
        src/MainMenu.cpp
        src/headers/MainMenu.h
        src/GamePlay.cpp
        src/headers/GamePlay.h)
file(COPY src/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(Snake PRIVATE sfml-graphics; sfml-window; sfml-system)
target_compile_features(Snake PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Snake
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Snake>
        VERBATIM)
endif()

install(TARGETS Snake)
