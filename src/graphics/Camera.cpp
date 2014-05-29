#include "Camera.h"

namespace astro
{

	Camera::Camera() :
		projection(Matrix4f(1.0f)),
		view(Matrix4f(1.0f))
	{

	}

	Camera::~Camera()
	{

	}

}
