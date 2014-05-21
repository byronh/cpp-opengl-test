#include "Logger.h"

#include <iostream>

namespace astro
{
	void Logger::debug(const std::string & message)
	{
		std::cout << message << std::endl;
	}
}