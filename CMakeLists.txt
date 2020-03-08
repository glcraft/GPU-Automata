cmake_minimum_required(VERSION 3.12)

project(glcompute_sample)

find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SFML COMPONENTS window CONFIG REQUIRED)

file(GLOB PROJECT_SRC
    "src/*.cpp"
    "include/*.h"
)
add_subdirectory(deps/libglw)

set(LIBGLW_LIBRARY_ONLY ON CACHE BOOL "RESERVED" FORCE)

add_executable(glcompute_sample ${PROJECT_SRC})
add_dependencies(glcompute_sample libglw)

target_link_libraries(glcompute_sample 
    glm
    GLEW::GLEW
    sfml-window
    libglw
)
