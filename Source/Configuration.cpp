#include <regex>

#include <Fall/Configuration.hpp>
#include <Fall/File.hpp>

namespace Fall
{
	Configuration::Configuration(const std::string & path)
	{
		readConfigurationFile(path);
	}

	std::string Configuration::getString(const std::string & key) const
	{
		std::string output;
		if (!tryGetString(key, output))
			throw Exception("Unable to find string in configuration file: " + key);
		return output;
	}

	std::string Configuration::getString(const std::string & key, const std::string & defaultValue) const
	{
		std::string output;
		if (!tryGetString(key, output))
			return defaultValue;
		return output;
	}

	bool Configuration::getBool(const std::string & key) const
	{
		bool output;
		if (!tryGetBool(key, output))
			throw Exception("Unable to find boolean in configuration file: " + key);
		return output;
	}

	bool Configuration::getBool(const std::string & key, bool defaultValue) const
	{
		bool output;
		if (!tryGetBool(key, output))
			return defaultValue;
		return output;
	}

	void Configuration::readConfigurationFile(const std::string & path)
	{
		std::string content;
		File::readFile(path, content);
		std::regex regex("^\\s*?(\\w+)(?: (.+?))?\r?$", std::regex_constants::ECMAScript);
		std::sregex_iterator begin(content.begin(), content.end(), regex);
		std::sregex_iterator end;
		for (auto i = begin; i != end; i++)
		{
			auto const & match = *i;
			const std::string & key = match[1];
			const std::string & value = match[2];
			if (_values.find(key) != _values.end())
				throw Exception("Encountered multiple definitions of key \"" + key + "\"");
			_values[key] = value;
		}
	}

	bool Configuration::tryGetString(const std::string & key, std::string & output) const
	{
		auto iterator = _values.find(key);
		if (iterator == _values.end())
			return false;
		output = iterator->second;
		return true;
	}

	bool Configuration::tryGetBool(const std::string & key, bool & output) const
	{
		unsigned value;
		if (!tryGetNumber<unsigned>(key, value))
			return false;
		if (value > 1)
			throw Exception("Invalid boolean value for key \"" + key + "\": " + std::to_string(value));
		output = value == 1;
		return true;
	}
}