#pragma once

#include <string>
#include <stdexcept>

namespace Fall
{
	class Exception
	{
	public:
		Exception();
		Exception(const std::string & message);

		const std::string & getMessage() const;

		const char * what() const;

	protected:
		std::string _message;
	};
}