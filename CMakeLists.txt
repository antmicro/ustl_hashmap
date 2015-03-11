cmake_minimum_required(VERSION 2.6)
project(ustl_hashmap)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(ustl_hashmap_SRCS ustl_hashmap.cpp main.cpp)

qt4_automoc(${ustl_hashmap_SRCS})
add_executable(ustl_hashmap ${ustl_hashmap_SRCS})
target_link_libraries(ustl_hashmap ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS ustl_hashmap RUNTIME DESTINATION bin)
