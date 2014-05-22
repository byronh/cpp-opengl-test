cmake_minimum_required (VERSION 2.8.5)
project (astro)
set (EXECUTABLE_NAME astro)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)

# Override default options in CMake subdirectories
SET (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
SET (GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW example programs")
SET (GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
SET (GLFW_INSTALL OFF CACHE BOOL "Generate the GLFW installation target")

# Libraries that need to be compiled by CMake
add_subdirectory (lib/glfw EXCLUDE_FROM_ALL)

# Libraries that need to be added to the include path
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/glm/)

# Source code files used in the executable
file (GLOB_RECURSE CPP_CODE
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
file (GLOB_RECURSE SHADER_CODE
	${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/*.glsl
)

# Organize source files into folders
source_group ("game" FILES ${CPP_CODE})
source_group ("shaders" FILES ${SHADER_CODE})

# Create executable from C++ source code only
add_executable (${EXECUTABLE_NAME} ${CPP_CODE} ${SHADER_CODE})

# Libraries that need to be linked to the executable
target_link_libraries (${EXECUTABLE_NAME} glfw)
target_link_libraries (${EXECUTABLE_NAME} ${GLFW_LIBRARIES})

# Define preprocessor macros
IF (TRUE)
	add_definitions (-DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
	add_definitions (-DSHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/")
ELSE ()
	add_definitions (-DASSET_DIR="$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/")
	add_definitions (-DSHADER_DIR="$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/")

	# Copy shader files to the distribution folder
	add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/src/shaders $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/shaders
	)

	# Copy assets to the distribution folder
	add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets
	)
ENDIF()
