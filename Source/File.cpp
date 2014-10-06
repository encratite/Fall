#include <cstdio>

#include <Fall/File.hpp>

namespace Fall
{
	File::File():
		_file(nullptr)
	{
	}

	File::File(const std::string & path, FileOpenMode mode) :
		_file(nullptr)
	{
		open(path, mode);
	}

	File::~File()
	{
		close();
	}

	void File::open(const std::string & path, FileOpenMode mode)
	{
		std::string modeString;
		switch (mode)
		{
		case FileOpenModeRead:
			modeString = "r";
			break;

		case FileOpenModeReadWrite:
			modeString = "r+";
			break;

		case FileOpenModeCreate:
			modeString = "a";
			break;
			
		case FileOpenModeTruncate:
			modeString = "w+";
			break;
		}

		modeString += "b";

		_file = std::fopen(path.c_str(), modeString.c_str());
		if (_file == nullptr)
			throw Exception("Failed to open file");

		if (mode == FileOpenModeCreate)
			seekBegin();
	}

	void File::close()
	{
		if (_file != nullptr)
		{
			std::fclose(_file);
			_file = nullptr;
		}
	}

	void File::read(char * buffer, std::size_t size)
	{
		checkFileDescriptor();
		std::fread(buffer, 1, size, _file);
		if (std::ferror(_file))
			closeAndThrow("Failed to read from file");
	}

	void File::read(std::string & output, std::size_t size)
	{
		char * buffer = nullptr;
		try
		{
			buffer = new char[size];
			read(buffer, size);
			output.assign(buffer, size);
		}
		catch (...)
		{
			if (buffer != nullptr)
				delete[] buffer;
			throw;
		}
	}

	std::string File::read(std::size_t size)
	{
		std::string output;
		read(output, size);
		return output;
	}

	void File::write(char const * buffer, std::size_t size)
	{
		checkFileDescriptor();
		std::fwrite(buffer, 1, size, _file);
		if (std::ferror(_file))
			closeAndThrow("Failed to write to file");
	}

	void File::write(const std::string & data)
	{
		write(data.c_str(), data.length());
	}

	void File::seekBegin()
	{
		checkFileDescriptor();
		setPosition(0);
	}

	void File::seekEnd()
	{
		checkFileDescriptor();
		if (std::fseek(_file, 0, SEEK_END) == -1)
			closeAndThrow("Failed to seek end of file");
	}

	long File::getPosition()
	{
		checkFileDescriptor();
		long position = std::ftell(_file);
		if (position == -1)
			closeAndThrow("Failed to determine position");
		return position;
	}

	void File::setPosition(long position)
	{
		checkFileDescriptor();
		if (std::fseek(_file, position, SEEK_SET) == -1)
			closeAndThrow("Failed to set position");
	}

	void File::checkFileDescriptor()
	{
		if (_file == nullptr)
			throw Exception("No file has been opened");
	}

	void File::readFile(const std::string & path, std::string & output)
	{
		File file(path, FileOpenModeRead);
		file.seekEnd();
		long fileSize = file.getPosition();
		file.seekBegin();
		file.read(output, static_cast<std::size_t>(fileSize));
		file.close();
	}

	void File::closeAndThrow(const std::string & message)
	{
		close();
		throw Exception(message);
	}
}