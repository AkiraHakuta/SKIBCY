# > mkdir build
# > cd build
# > cmake -G "MinGW Makefiles" ..
# > mingw32-make.exe  
# > skibcy.exe ../test.txt

cmake_minimum_required(VERSION 3.6)

project(skibcy) 
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DANTLR4CPP_STATIC)

set(ANTLR4_ROOT C:/antlr4/antlr4-4.13.2)
list(APPEND CMAKE_MODULE_PATH ${ANTLR4_ROOT}/cmake)
set(ANTLR_EXECUTABLE C:/Javalib/antlr-4.13.2-complete.jar)

include_directories(${ANTLR4_ROOT}/include/antlr4-runtime)

add_library(antlr4_static STATIC IMPORTED)
set_target_properties(antlr4_static PROPERTIES IMPORTED_LOCATION ${ANTLR4_ROOT}/lib/libantlr4-runtime-static.a)

find_package(ANTLR REQUIRED)
antlr_target(combinatorGrammar combinator.g4 VISITOR)
include_directories(${ANTLR_combinatorGrammar_OUTPUT_DIR})

add_executable(skibcy skibcy.cpp convert.cpp ${ANTLR_combinatorGrammar_CXX_OUTPUTS})
target_link_libraries(skibcy antlr4_static)
target_link_libraries(skibcy -static -lstdc++ -lgcc -lwinpthread)