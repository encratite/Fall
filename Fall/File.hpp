#pragma once

#include <cstdio>
#include <string>

#include <Fall/Exception.hpp>

namespace Fall
{
	enum FileOpenMode
	{
		FileOpenModeRead,
		FileOpenModeReadWrite,
		FileOpenModeCreate,
		FileOpenModeTruncate
	};

	class File
	{
	public:
		File();
		File(const std::string & path, FileOpenMode mode);
		~File();

		void open(const std::string & path, FileOpenMode mode);
		void close();

		void read(char * buffer, std::size_t size);
		void read(std::string & output, std::size_t size);
		std::string read(std::size_t size);

		void write(char const * buffer, std::size_t size);
		void write(const std::string & data);

		void seekBegin();
		void seekEnd();

		long getPosition();
		void setPosition(long position);

		static void readFile(const std::string & path, std::string & output);

	private:
		FILE * _file;

		void checkFileDescriptor();
		void closeAndThrow(const std::string & message);
	};
}