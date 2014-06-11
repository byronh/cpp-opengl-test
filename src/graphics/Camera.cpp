#include "Camera.h"

namespace astro
{

	Camera::Camera() :
		_projection(Matrix4f(1.0f)),
		_view(Matrix4f(1.0f)),
		_dirty(true)
	{

	}

	Camera::Camera(const Matrix4f & projection, const Matrix4f & view) :
		_projection(projection),
		_view(view),
		_dirty(true)
	{
		
	}

	Camera::~Camera()
	{

	}

	const Matrix4f & Camera::getProjectionMatrix() const
	{
		return _projection;
	}

	const Matrix4f & Camera::getViewMatrix() const
	{
		return _view;
	}

	const Matrix4f & Camera::getCombinedMatrix()
	{
		if (_dirty)
		{
			_combined = _projection * _view;
			_dirty = false;
		}
		return _combined;
	}

}
