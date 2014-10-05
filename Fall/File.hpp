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
		File(std::string const & path, FileOpenMode mode);
		~File();

		void open(std::string const & path, FileOpenMode mode);
		void close();

		void read(char * buffer, std::size_t size);
		void read(std::string & output, std::size_t size);
		std::string read(std::size_t size);

		void write(char const * buffer, std::size_t size);
		void write(std::string const & data);

		void seekBegin();
		void seekEnd();

		long getPosition();
		void setPosition(long position);

		static void readFile(std::string const & path, std::string & output);

	private:
		FILE * _file;

		void checkFileDescriptor();
		void closeAndThrow(std::string const & message);
	};
}