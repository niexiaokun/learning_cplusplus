cmake_minimum_required(VERSION 3.15)
project(learning_cplusplus)

set(CMAKE_CXX_STANDARD 17)

add_executable(list_support_multiTypes list_support_multiTypes.cpp)
add_executable(singleton singleton.cpp)
add_executable(smartPtr smartPtr.cpp)
add_executable(mat mat.cpp)


target_link_libraries(singleton pthread)