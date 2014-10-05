#pragma once

#include <string>
#include <sstream>

#include <Fall/Exception.hpp>

namespace Fall
{
	template <typename NumericType>
		bool stringToNumber(std::string const & input, NumericType & output, std::ios_base::fmtflags base = std::ios_base::dec)
	{
		NumericType output;
		std::stringstream stream(input);
		stream.setf(base, std::ios_base::basefield);
		if ((stream >> output) == 0)
			return false;
		return true;
	}

	template <typename NumericType>
		NumericType stringToNumber(std::string const & input, std::ios_base::fmtflags base = std::ios_base::dec)
	{
		NumericType output;
		if(!stringToNumber<NumericType>(input, output))
			throw Exception("Failed to convert string to numeric type");
		return output;
	}

	template <typename NumericType>
		std::string numberToString(NumericType input, std::ios_base::fmtflags base = std::ios_base::dec)
	{
		std::string output;
		std::stringstream stream;
		stream.setf(base, std::ios_base::basefield);
		stream << input;
		stream >> output;
		return output;
	}
}