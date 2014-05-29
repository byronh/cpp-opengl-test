#include "../core/Core.h"

namespace astro
{

	class VertexAttributes
	{

	public:

		enum AttributeType
		{
			ATTRIBUTETYPE_POSITION = 1,
			ATTRIBUTETYPE_COLOR = 2,
		};

		int mask;

	};

}