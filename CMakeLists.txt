cmake_minimum_required (VERSION 2.8.5)
project (astro)
set (EXECUTABLE_NAME astro)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)

# Override default options in CMake subdirectories
SET (BUILD_SHARED_LIBS OFF CACHE BOOL "Build a shared version of the library")
SET (ASSIMP_ENABLE_BOOST_WORKAROUND ON CACHE BOOL "If a simple implementation of the used Boost functions is used. Slightly reduces functionality, but enables builds without Boost available.")
SET (ASSIMP_BUILD_TESTS OFF CACHE BOOL "If the test suite for Assimp is built in addition to the library.")
SET (ASSIMP_NO_EXPORT ON CACHE BOOL "Disable Assimp's export functionality.")
SET (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
SET (GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW example programs")
SET (GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
SET (GLFW_INSTALL OFF CACHE BOOL "Generate the GLFW installation target")

# Subprojects
add_subdirectory (lib/assimp EXCLUDE_FROM_ALL)
add_subdirectory (lib/glfw EXCLUDE_FROM_ALL)

# Static libraries
file (GLOB_RECURSE SOIL_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/lib/soil/src/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/lib/soil/src/*.c
)
add_library(soil STATIC ${SOIL_SOURCES})

# Libraries that need to be added to the include path
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/assimp/include)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/glm/)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib/soil/src)

# Source code files used in the executable
file (GLOB_RECURSE CPP_CODE
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Organize C++ source files into folders
foreach(f ${CPP_CODE})
	file(RELATIVE_PATH SOURCE_GROUP ${CMAKE_CURRENT_SOURCE_DIR}/src ${f})
	set(SOURCE_GROUP "game/${SOURCE_GROUP}")
	string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SOURCE_GROUP ${SOURCE_GROUP})
	string(REPLACE / \\ SOURCE_GROUP ${SOURCE_GROUP})
	source_group("${SOURCE_GROUP}" FILES ${f})
endforeach()

# Organize other files into folders
file (GLOB_RECURSE SHADER_CODE
	${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/*.glsl
)
source_group ("shaders" FILES ${SHADER_CODE})

# Create executable
add_executable (${EXECUTABLE_NAME} ${CPP_CODE} ${SHADER_CODE})

# Libraries that need to be linked to the executable
target_link_libraries (${EXECUTABLE_NAME} assimp)
target_link_libraries (${EXECUTABLE_NAME} glfw)
target_link_libraries (${EXECUTABLE_NAME} ${GLFW_LIBRARIES})
target_link_libraries (${EXECUTABLE_NAME} soil)

# Define preprocessor macros
IF (APPLE)
	add_definitions (-DAPPLE)
ENDIF ()
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
ENDIF ()
