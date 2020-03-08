cmake_minimum_required(VERSION 3.12)

project(glcompute_sample)

find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SFML COMPONENTS window CONFIG REQUIRED)

file(GLOB PROJECT_SRC
    "src/*.cpp"
    "include/*.h"
)

add_executable(glcompute_sample ${PROJECT_SRC})

target_link_libraries(glcompute_sample 
    glm
    GLEW::GLEW
    sfml-window
)