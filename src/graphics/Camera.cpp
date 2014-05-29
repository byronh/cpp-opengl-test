#include "Camera.h"

namespace astro
{

	Camera::Camera() :
		projection(Matrix4f(1.0f)),
		view(Matrix4f(1.0f))
	{

	}

	Camera::Camera(const Matrix4f & projectionMatrix, const Matrix4f & viewMatrix)
	{
		projection = projectionMatrix;
		view = viewMatrix;
	}

	Camera::~Camera()
	{

	}

	const Matrix4f & Camera::getProjectionMatrix() const
	{
		return projection;
	}

	const Matrix4f & Camera::getViewMatrix() const
	{
		return view;
	}

}
