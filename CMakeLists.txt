cmake_minimum_required(VERSION 3.21)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps/glfw)

add_executable(video-app src/main.cpp)
target_link_libraries(video-app glfw)

if(APPLE)
    target_link_libraries(video-app "-framework OpenGL")
elseif(WIN32)
    target_link_libraries(video-app -lglu32 -lopengl32)
else()
    target_link_libraries(video-app -lGL -lGLU -lX11)
endif()
