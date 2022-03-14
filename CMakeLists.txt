cmake_minimum_required(VERSION 3.0.0)
project(GRAPH_COLORING VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

file(GLOB src_files
    "src/*.cpp"
)

add_executable(graph_coloring main.cpp ${src_files})

set_target_properties(graph_coloring
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR})