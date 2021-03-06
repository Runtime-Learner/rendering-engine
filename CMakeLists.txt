cmake_minimum_required(VERSION 3.0.0)

project(Rendering_Engine_Cpp VERSION 0.1.0)

# add the executable
add_executable(Rendering_Engine_Cpp  WIN32 src/main.cpp)

# add eigen library
include_directories(lib)

# add SDL2 library
add_subdirectory(lib/SDL2-2.0.20)

# add the libraries
add_subdirectory(src/Cameras)
add_subdirectory(src/Lights)
add_subdirectory(src/Ray)
add_subdirectory(src/Renderers)
add_subdirectory(src/Scenes)
add_subdirectory(src/Shapes)
add_subdirectory(src/BxDFs)

target_link_libraries(Rendering_Engine_Cpp PUBLIC Cameras)
target_link_libraries(Rendering_Engine_Cpp PUBLIC Lights)
target_link_libraries(Rendering_Engine_Cpp PUBLIC Ray)
target_link_libraries(Rendering_Engine_Cpp PUBLIC Renderers)
target_link_libraries(Rendering_Engine_Cpp PUBLIC Scenes)
target_link_libraries(Rendering_Engine_Cpp PUBLIC Shapes)
target_link_libraries(Rendering_Engine_Cpp PUBLIC BxDFs)
target_link_libraries(Rendering_Engine_Cpp PUBLIC SDL2)

#find_package(OpenMP)
#if(OpenMP_CXX_FOUND)
#    target_link_libraries(Rendering_Engine_Cpp PUBLIC OpenMP::OpenMP_CXX)
#endif()

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
