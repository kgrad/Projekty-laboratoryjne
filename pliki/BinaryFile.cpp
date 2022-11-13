#include "BinaryFile.h"
using namespace std;

BinaryFile::BinaryFile(const std::string path, const std::string mode)
{


	if (mode.find("r") != std::string::npos) openMode |= std::fstream::in;
	if (mode.find("w") != std::string::npos) openMode |= std::fstream::out;
	if (mode.find("a") != std::string::npos) openMode |= std::fstream::app;
	if (mode.find("t") != std::string::npos) openMode |= std::fstream::trunc;
	if (mode.find("e") != std::string::npos) openMode |= std::fstream::ate;
	if (mode.find("b") != std::string::npos) openMode |= std::fstream::binary;

	this->filePath = path;
	this->openMode = openMode;
	file.open(path, openMode);
}


BinaryFile::~BinaryFile()
{
	file.close();

}

FileError BinaryFile::Write(const std::vector<Point>& v)
{
	FileError retVal = FileError(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (openMode & std::fstream::out)
	{
		file.write((const char*)v.data(), v.size() * sizeof(Point));
		retVal = FileError(SUCCESS);
	}

	return retVal;
}

FileError BinaryFile::Read(std::vector<Point>& v)
{
	FileError retVal = FileError(ACCESS_DENIED);
	file.seekg(0, file.end);
	int roz = file.tellg();
	file.seekg(0, file.beg);
	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (roz <= 0) {
		return FileError::OUT_OF_BOUNDS;
	}
	else if (openMode & std::fstream::in)
	{
		v.clear();
		v.resize(roz / sizeof(Point));
		file.seekg(0, std::fstream::beg);
		file.read((char *)v.data(), roz);
		retVal = FileError(SUCCESS);
	}

	return retVal;
}

FileError BinaryFile::Read(Point& p, const unsigned long idx)
{
	FileError retVal = FileError(ACCESS_DENIED);
	file.seekg(0, file.end);
	int roz = file.tellg();
	file.seekg(0, file.beg);
	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (idx * sizeof(Point) >= roz) {
		retVal= FileError::OUT_OF_BOUNDS;
		}
		
	else if (openMode & std::fstream::in)
	{
		file.seekg(idx * sizeof(Point));
		file.read((char*)(&p), sizeof(Point));
		retVal = FileError(SUCCESS);
	}

	return retVal;
}
