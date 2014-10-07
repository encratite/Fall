#pragma once

#include <string>
#include <stdexcept>

namespace Fall
{
	class Exception: public std::exception
	{
	public:
		Exception();
		Exception(const std::string & message);

		const std::string & getMessage() const;

		const char * what() const noexcept;

	protected:
		std::string _message;
	};
}