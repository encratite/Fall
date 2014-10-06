#include <Fall/Configuration.hpp>
#include <Fall/File.hpp>
#include <Fall/String.hpp>

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
		try
		{
			File::readFile(path, content);
		}
		catch (...)
		{
			return;
		}
		std::stringstream stream(content);
		std::string line;
		while (std::getline(stream, line))
		{
			line = trim(line);
			if (line.empty() || line[0] == '#')
				continue;
			std::string key, value;
			std::size_t index = line.find(' ');
			if (index != std::string::npos)
			{
				key = line.substr(0, index);
				key = trim(key);
				if (key.empty())
					throw Exception("Encountered an empty key in a configuration file");
				value = line.substr(index + 1);
			}
			else
			{
				key = line;
			}
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