#pragma once

#include <string>

namespace astro
{
	class Logger
	{

	public:

		static void error(const std::string & message);
		static void debug(const std::string & message);

	};
}