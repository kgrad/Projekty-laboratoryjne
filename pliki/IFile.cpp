#include "IFile.h"
using namespace std;

IFile::IFile(const string filePath, const string mode) : filePath(filePath), openMode(0), length(0)
{
	if (mode.find("r") != std::string::npos) openMode |= std::fstream::in;
	if (mode.find("w") != std::string::npos) openMode |= std::fstream::out;
	if (mode.find("a") != std::string::npos) openMode |= std::fstream::app;
	if (mode.find("t") != std::string::npos) openMode |= std::fstream::trunc;
	if (mode.find("e") != std::string::npos) openMode |= std::fstream::ate;
	if (mode.find("b") != std::string::npos) openMode |= std::fstream::binary;

	file.open(filePath, openMode);
	if (file.is_open())
	{
		file.seekg(0, fstream::end);
		length = file.tellg();
		file.seekg(0, fstream::beg);
	}
}

IFile::~IFile()
{
	file.close();
}

