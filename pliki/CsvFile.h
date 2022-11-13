#pragma once
#include "Point.h"
#include <fstream>
#include <vector>
#include "IFile.h"
#include "FileError.h"
using namespace std;
    class CsvFile : public IFile
    {
        void WriteLine(const Point&);
        vector<string> Split(std::string str, char delim);
    public:
        CsvFile(const string, const string);
        ~CsvFile();

        FileError Write(const vector<Point>&) override;
        FileError Read(vector<Point>&)override;
        FileError Read(Point&, const unsigned long)override;
    };