cmake_minimum_required(2.8)
project(FSMLanguage)

## Version settings
SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")
SET(VERSION_PATCH "0")

SET (CMAKE_BUILD_TYPE Release) # Default build type is release

## include path configuration
include_directories(src)

## Flex/Bison configuration
find_package(BISON)
find_package(FLEX)

FLEX_TARGET(MyScanner ${CMAKE_CURRENT_SOURCE_DIR}/src/lex.l
${CMAKE_CURRENT_BINARY_DIR}/lex.cpp COMPILE_FLAGS -w)
BISON_TARGET(MyParser ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y
${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
include_directories(${CMAKE_CURRENT_BINARY_DIR})


## CPP Compiler 
## TODO: add gcc support and windows support
SET (CMAKE_CXX_COMPILER_ENV_VAR "clang++")
SET (CMAKE_CXX_FLAGS "-std=c++11")
SET (CMAKE_CXX_FLAGS_DEBUG "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")


## Source code configuration
file(GLOB_RECURSE source_files	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM  source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB_RECURSE runtime_files ${CMAKE_CURRENT_SOURCE_DIR}/runtime/*.cpp)

add_library(fsmrt ${runtime_files})
add_library(fsm ${runtime_files})
add_executable(fsmc ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(fsmc fsm)

install(TARGETS fsmrt ARCHIVE DESTINATION lib)
install(TARGETS fsm ARCHIVE DESTINATION lib)
install(TARGETS fsmc RUNTIME DESTINATION bin)