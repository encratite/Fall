#pragma once

#include <string>
#include <stdexcept>

namespace Fall
{
	class Exception
	{
	public:
		Exception(std::string const & message);

		std::string const & getMessage() const;

	protected:
		std::string _message;
	};
}