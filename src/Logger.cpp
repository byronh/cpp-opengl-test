#include "Logger.h"

#include <iostream>

namespace astro
{
	void Logger::error(const std::string & message)
	{
		std::cerr << message << std::endl;
	}

	void Logger::debug(const std::string & message)
	{
		std::cout << message << std::endl;
	}
}