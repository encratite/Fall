#pragma once

#include <string>
#include <sstream>
#include <map>

#include <Fall/Exception.hpp>

namespace Fall
{
	typedef std::map<std::string, std::string> ConfigurationMap;
	
	class Configuration
	{
	public:
		Configuration(const std::string & path);

		std::string getString(const std::string & key) const;
		std::string getString(const std::string & key, const std::string & defaultValue) const;

		bool getBool(const std::string & key) const;
		bool getBool(const std::string & key, bool defaultValue) const;
		
		template <typename NumericType>
			NumericType getNumber(const std::string & key) const
		{
			NumericType output;
			if (!tryGetNumber<NumericType>(key, output))
				throw Exception("Unable to find numeric value in configuration file: " + key);
			return output;
		}

		template <typename NumericType>
			NumericType getNumber(const std::string & key, NumericType defaultValue) const
		{
			NumericType output;
			if (!tryGetNumber<NumericType>(key, output))
				return defaultValue;
			return output;
		}

	private:
		ConfigurationMap _values;

		void readConfigurationFile(const std::string & path);

		bool tryGetString(const std::string & key, std::string & output) const;
		bool tryGetBool(const std::string & key, bool & output) const;

		
		template <typename NumericType>
			bool tryGetNumber(const std::string & key, NumericType & output) const
		{
			std::string numberString;
			if (!tryGetString(key, numberString))
				return false;
			try
			{
				std::stringstream stream(numberString);
				stream >> output;
				return true;
			}
			catch (...)
			{
				throw Exception("Invalid numeric value for key \"" + key + "\" in configuration file: " + numberString);
			}
		}
	};
}