#include <Fall/Time.hpp>

#include <ctime>

namespace Fall
{
	std::string timestamp()
	{
		std::time_t time = std::time(nullptr);
		std::tm * localTime = std::localtime(&time);
		char buffer[128];
		std::size_t size = std::strftime(buffer, sizeof(buffer), "%F %T", localTime);
		std::string output(buffer, size);
		return output;
	}
}