cmake_minimum_required(VERSION 3.0.0)
project(learnopengl VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES arm64)

include(CTest)
enable_testing()

# find_package(glfw3 REQUIRED)
# include_directories(${GLFW3_INCLUDE_DIR})

# find_package(glew REQUIRED)
# include_directories(${GLFW3_INCLUDE_DIR})

include_directories("glad/include")

include_directories("/opt/homebrew/Cellar/glfw/3.3.6/include")
link_directories("/opt/homebrew/Cellar/glfw/3.3.6/lib")

add_executable(learnopengl main.cpp "glad/src/glad.c")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# target_link_libraries(learnopengl glfw)