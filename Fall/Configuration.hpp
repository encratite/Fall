#pragma once

#include <string>
#include <map>

#include <Fall/Exception.hpp>

namespace Fall
{
	class Configuration
	{
	public:
		Configuration(std::string const & path);

		std::string getString(std::string const & key) const;
		std::string getString(std::string const & key, std::string const & defaultValue) const;

		int getInt(std::string const & key) const;
		int getInt(std::string const & key, int defaultValue) const;

		bool getBool(std::string const & key) const;
		bool getBool(std::string const & key, bool defaultValue) const;

	private:
		std::map<std::string, std::string> _values;

		void readConfigurationFile(std::string const & path);

		bool tryGetString(std::string const & key, std::string & output) const;
		bool tryGetInt(std::string const & key, int & output) const;
		bool tryGetBool(std::string const & key, bool & output) const;
	};
}