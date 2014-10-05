#include <regex>

#include <Fall/Configuration.hpp>
#include <Fall/File.hpp>
#include <Fall/String.hpp>

namespace Fall
{
	Configuration::Configuration(std::string const & path)
	{
		readConfigurationFile(path);
	}

	std::string Configuration::getString(std::string const & key) const
	{
		std::string output;
		if (!tryGetString(key, output))
			throw Exception("Unable to find string key in configuration file: " + key);
		return output;
	}

	std::string Configuration::getString(std::string const & key, std::string const & defaultValue) const
	{
		std::string output;
		if (!tryGetString(key, output))
			return defaultValue;
		return output;
	}

	int Configuration::getInt(std::string const & key) const
	{
		int output;
		if(!getInt(key, output))
			throw Exception("Unable to find integer key in configuration file: " + key);
		return output;
	}

	int Configuration::getInt(std::string const & key, int defaultValue) const
	{
		int output;
		if (!getInt(key, output))
			return defaultValue;
		return output;
	}

	bool Configuration::getBool(std::string const & key) const
	{
		int output;
		if (!getInt(key, output))
			throw Exception("Unable to find boolean key in configuration file: " + key);
		return output;
	}

	bool Configuration::getBool(std::string const & key, bool defaultValue) const
	{
		int output;
		if (!getInt(key, output))
			return defaultValue;
		return output;
	}

	void Configuration::readConfigurationFile(std::string const & path)
	{
		std::string content;
		File::readFile(path, content);
		std::regex regex("^([^ ]+?)(?: ([^\\r]+))?$", std::regex_constants::extended);
		std::sregex_iterator begin(content.begin(), content.end(), regex);
		std::sregex_iterator end;
		for (auto i = begin; i != end; i++)
		{
			auto const & match = *i;
			std::string const & key = match[1];
			std::string const & value = match[2];
			if (_values.find(key) != _values.end())
				throw Exception("Encountered multiple definitions of key \"" + key + "\"");
			_values[key] = value;
		}
	}

	bool Configuration::tryGetString(std::string const & key, std::string & output) const
	{
		auto iterator = _values.find(key);
		if (iterator == _values.end())
			return false;
		output = iterator->second;
		return true;
	}

	bool Configuration::tryGetInt(std::string const & key, int & output) const
	{
		std::string intString;
		if (!tryGetString(key, intString))
			return false;
		if (!stringToNumber<int>(intString, output))
			throw Exception("Invalid integer for key \"" + key + "\" in configuration file: " + intString);
		return true;
	}

	bool Configuration::tryGetBool(std::string const & key, bool & output) const
	{
		int intValue;
		if (!tryGetInt(key, intValue))
			return false;
		if (intValue < 0 || intValue > 1)
			throw Exception("Invalid boolean value for key \"" + key + "\": " + numberToString(intValue));
		output = intValue == 1;
		return true;
	}
}