#include <sstream>

#include <Fall/String.hpp>

namespace Fall
{
	bool isWhitespace(char character)
	{
		return character == '\t' || character == '\n' || character == '\r' || character == ' ';
	}

	std::string trim(std::string const & string)
	{
		std::size_t left = 0;
		std::size_t right = string.length();
		while (left < right)
		{
			if (!isWhitespace(string.at(left)))
				break;
			left++;
		}
		while (right > left + 1)
		{
			if (!isWhitespace(string.at(right - 1)))
				break;
			right--;
		}
		std::string output = string.substr(left, right - left);
		return output;
	}
}