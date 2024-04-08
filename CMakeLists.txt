cmake_minimum_required(VERSION 3.23.0)
project(cae VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

set(PROFILE FALSE)
if (PROFILE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    if (APPLE)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
        if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mno-omit-leaf-frame-pointer")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mno-omit-leaf-frame-pointer")
        endif()
    endif ()
endif ()

find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
endif()

set(FILESYSTEM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/include)
set(GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm/include)
set(GLAD_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)
set(STB_IMAGE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/image/include)
set(KHR_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/KHR/include)
set(GLAD
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include/glad/glad.h)
set(STB_IMAGE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/image/src/stb_image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/image/include/image/stb_image.h)
set(FILESYSTEM
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/src/filesystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/include/filesystem/filesystem.h)

file(GLOB_RECURSE IMGUI "libs/imgui/*")

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

set(COMPILATION_UNIT
        src/main.cpp
        ${GLAD}
        ${STB_IMAGE}
        ${FILESYSTEM}
        ${IMGUI}
        ${SOURCES}
        )

add_executable(${PROJECT_NAME} ${COMPILATION_UNIT})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${GLAD_INCLUDE_DIRS}
        ${FILESYSTEM_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${STB_IMAGE_INCLUDE_DIRS}
        ${KHR_INCLUDE_DIRS}
        )

target_link_libraries(${PROJECT_NAME} OpenGL::GL ${SDL2_LIBRARIES})
