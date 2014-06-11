#include "../core/Core.h"

namespace astro
{

	class Camera
	{

	public:

		Camera();
		Camera(const Matrix4f & projection, const Matrix4f & view);
		~Camera();

		const Matrix4f & getProjectionMatrix() const;
		const Matrix4f & getViewMatrix() const;
		const Matrix4f & getCombinedMatrix();

	private:

		Matrix4f _projection;
		Matrix4f _view;
		Matrix4f _combined;

		bool _dirty;

	};


}