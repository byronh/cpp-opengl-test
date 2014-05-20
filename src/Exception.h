#pragma once

#include <stdexcept>
#include <string>

namespace astro
{
	class Exception : public std::runtime_error
	{

	public:
		explicit Exception(const std::string & msg) : std::runtime_error(msg) {}

	};
}