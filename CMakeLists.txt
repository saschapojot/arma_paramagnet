cmake_minimum_required(VERSION 3.27)
project(arma_paramagnet)

set(CMAKE_CXX_STANDARD 20)

add_executable(ap main.cpp)
set_source_files_properties(
        main.cpp
        PROPERTIES

        COMPILE_OPTIONS "-O3"
)


include_directories("/home/polya/cppLocal/armadillo/include")
file(GLOB LIBS_SO "/home/polya/cppLocal/armadillo/lib/*.so")
target_link_libraries(ap ${LIBS_SO})