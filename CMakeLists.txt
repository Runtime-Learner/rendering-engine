cmake_minimum_required(VERSION 3.0.0)

project(Rendering_Engine_Cpp VERSION 0.1.0)

# add the executable
add_executable(Rendering_Engine_Cpp src/main.cpp)

target_link_libraries(Rendering_Engine_Cpp SDL2)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)