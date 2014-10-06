#include <Fall/Configuration.hpp>

int main()
{
	Fall::Configuration configuration("Configuration.conf");
	std::string stringValue = configuration.getString("stringValue");
	std::string emptyStringValue = configuration.getString("emptyStringValue");
	int intValue = configuration.getNumber<int>("intValue");
	unsigned unsignedValue = configuration.getNumber<unsigned>("unsignedValue");
	float floatValue = configuration.getNumber<float>("floatValue");
	bool boolValue = configuration.getBool("boolValue");
	return 0;
}