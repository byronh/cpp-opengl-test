cmake_minimum_required (VERSION 2.8.5)
project (astro)
set (EXECUTABLE_NAME "astro")

# Libraries that need to be compiled by CMake
add_subdirectory (lib/glfw EXCLUDE_FROM_ALL)

# Libraries that need to be added to the include path
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/glm/)

# Source code files used in the executable
file (GLOB_RECURSE CODE
	${CMAKE_CURRENT_SOURCE_DIR}/src/*
)
add_executable (${EXECUTABLE_NAME} ${CODE})

# Libraries that need to be linked to the executable
target_link_libraries (${EXECUTABLE_NAME} glfw)
target_link_libraries (${EXECUTABLE_NAME} ${GLFW_LIBRARIES})

# Designate install destination folder
install (TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dist)