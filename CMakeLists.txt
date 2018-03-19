cmake_minimum_required(VERSION 3.6)
project(GL_Surface)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)

add_subdirectory(./lib)
include_directories(${SDL2_SOURCE_DIR}/include ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE} ${GLM_INCLUDE_DIR})

file(GLOB_RECURSE SOURCE_FILES
        "src/*.cpp"
        "src/*.h"
        )


add_executable(GL_Surface ${SOURCE_FILES})

target_link_libraries(GL_Surface SDL2-static SDL2main ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLM_LIBRARIES})

file(COPY res/ DESTINATION res/)


