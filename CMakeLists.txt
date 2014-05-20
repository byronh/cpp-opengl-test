cmake_minimum_required(VERSION 2.8.5)
project(astro)

set(EXECUTABLE_NAME "astro")


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})


file(GLOB_RECURSE CODE
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)


# Libraries that need to be compiled by CMake
##ADD_DEFINITIONS(-DGLEW_STATIC)

#add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

# Libraries that need to be added to the include path
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/glew/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/glm/)

# Libraries that need to be linked to the executable
add_executable(${EXECUTABLE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

#SET_TARGET_PROPERTIES(${EXECUTABLE_NAME} PROPERTIES COMPILE_DEFINITIONS "GLEW_STATIC=")
#target_link_libraries(${EXECUTABLE_NAME} libglew_static)
target_link_libraries(${EXECUTABLE_NAME} glfw)
target_link_libraries(${EXECUTABLE_NAME} ${GLFW_LIBRARIES})

