#pragma once
#include "Point.h"
#include <fstream>
#include "FileError.h"
#include <string> 
#include <vector>
#include "IFile.h"
using namespace std;
class BinaryFile : public IFile
{

public:
    BinaryFile(const std::string path, const std::string mode);
    ~BinaryFile();

    FileError Write(const vector<Point>&) override;
    FileError Read(vector<Point>&) override;
    FileError Read(Point&, const unsigned long) override;
};