#include <Fall/Exception.hpp>

namespace Fall
{
	Exception::Exception():
		_message("Error")
	{
	}
	
	Exception::Exception(const std::string & message):
		_message(message)
	{
	}

	const std::string & Exception::getMessage() const
	{
		return _message;
	}

	const char * Exception::what() const noexcept
	{
		return _message.c_str();
	}
}