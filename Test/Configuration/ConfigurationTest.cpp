#include <Fall/Configuration.hpp>

int main()
{
	Fall::Configuration configuration("configuration");
	std::string stringValue = configuration.getString("stringValue");
	std::string emptyStringValue = configuration.getString("emptyStringValue");
	int intValue = configuration.getInt("intValue");
	bool boolValue = configuration.getBool("boolValue");
	return 0;
}