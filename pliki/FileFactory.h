#pragma once
#include <string>
#include "IFile.h"
#include "BinaryFile.h"
#include "CsvFile.h"

static class FileFactory
{
public:
	static IFile* OpenFile(const std::string, const std::string);
	
};

