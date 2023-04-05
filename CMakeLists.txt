cmake_minimum_required(VERSION 3.0.0)
project(P2-Template VERSION 1.0.0)
target_include_directories(P2-Template /include /src)
add_executable(P2-Template 
main.cpp

)
target_link_libraries(P2-Template glfw)