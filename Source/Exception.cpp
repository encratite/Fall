#include <Fall/Exception.hpp>

namespace Fall
{
	Exception::Exception():
		_message("Error")
	{
	}
	
	Exception::Exception(std::string const & message):
		_message(message)
	{
	}

	std::string const & Exception::getMessage() const
	{
		return _message;
	}
}