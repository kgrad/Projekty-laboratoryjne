#pragma once
#include <fstream>
#include <vector>
#include "FileError.h"
#include "Point.h"
#include <string>

using namespace std;

class IFile
{
protected:
    fstream file;
    string filePath;
    unsigned long length;
    fstream::openmode openMode;
     
public:
    IFile(const string = string(), const string = string());
    virtual ~IFile();

    enum Error
    {
        SUCCESS,
        ACCESS_DENIED,
        OUT_OF_BOUNDS,
        FILE_INVALID
    };

    virtual FileError Write(const vector<Point>&) = 0;
    virtual FileError Read(vector<Point>&) = 0;
    virtual FileError Read(Point&, const unsigned long) = 0;

};