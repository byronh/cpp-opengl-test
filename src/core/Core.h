#pragma once

#include "Exception.h"

#include "../utils/OpenGL.h"
#define GLM_FORCE_RADIANS
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace astro
{

	typedef GLuint Handle;

	typedef glm::vec2 Vector2f;
	typedef glm::vec3 Vector3f;
	typedef glm::vec4 Vector4f;
	typedef glm::mat4x4 Matrix4f;

}