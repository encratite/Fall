#include <cstdio>
#include <mutex>

#include <Fall/Console.hpp>
#include <Fall/Time.hpp>

namespace
{
	std::mutex consoleMutex;
}

namespace Fall
{
	void write(const std::string & text)
	{
		std::lock_guard<std::mutex> lock(consoleMutex);
		fwrite(text.c_str(), 1, text.length(), stdout);
	}
	
	void writeLine(const std::string & text)
	{
		write(text + "\n");
	}
	
	void log(const std::string & text)
	{
		writeLine(timestamp() + " " + text);
	}
}