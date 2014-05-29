#include "../core/Core.h"

namespace astro
{

	class Camera
	{

	public:

		Camera();
		Camera(const Matrix4f & projectionMatrix, const Matrix4f & viewMatrix);
		~Camera();

		const Matrix4f & getProjectionMatrix() const;
		const Matrix4f & getViewMatrix() const;

	private:

		Matrix4f projection;
		Matrix4f view;

	};


}