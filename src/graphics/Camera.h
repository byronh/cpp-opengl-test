#include "../core/Core.h"

namespace astro
{

	class Camera
	{

	public:

		Camera();
		~Camera();

		Matrix4f projection;
		Matrix4f view;

	};


}