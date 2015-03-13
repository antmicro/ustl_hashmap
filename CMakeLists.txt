cmake_minimum_required(VERSION 2.6)
project(ustl_hashmap)
include_directories("../ustl/")
find_library(ustl ustl "../ustl/.o/")
message(${ustl})
set(ustl_hashmap_SRCS ustl_hashmap.cpp)

add_executable(ustl_hashmap ${ustl_hashmap_SRCS})
target_link_libraries(ustl_hashmap ${ustl})
target_compile_options(ustl_hashmap PRIVATE "-nodefaultlibs" PRIVATE "-lc" PRIVATE "--std=c++11" PRIVATE "-g" PRIVATE "-Wall")

install(TARGETS ustl_hashmap RUNTIME DESTINATION bin)
