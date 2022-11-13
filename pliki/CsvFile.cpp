#include "CsvFile.h";
#include "FileError.h";
#include <iostream>;
#include <string>;
#include <sstream>;
using namespace std;
CsvFile::CsvFile(const string path, const string mode)
{
	if (mode.find("r") != string::npos) openMode |= fstream::in;
	if (mode.find("w") != string::npos) openMode |= fstream::out;
	if (mode.find("a") != string::npos) openMode |= fstream::app;
	if (mode.find("t") != string::npos) openMode |= fstream::trunc;
	if (mode.find("e") != string::npos) openMode |= fstream::ate;
	if (mode.find("b") != string::npos) openMode |= fstream::binary;
	this->filePath = path;
	this->openMode = openMode;
	file.open(path, openMode);
}

CsvFile::~CsvFile()
{
	file.close();
}

void CsvFile::WriteLine(const Point & v)
{
	FileError retVal = FileError(ACCESS_DENIED);
	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (openMode & fstream::out)
	{
		ostringstream strs;
		strs << v.x << " "<< v.y<<" "<<v.z<<" "<<endl;
		string str = strs.str();
		file<<(str);
		retVal = FileError(SUCCESS);
	}
}

vector<string> CsvFile::Split(string str, char delim)
{
	vector<string> result;
	stringstream ss(str);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}


FileError CsvFile::Write(const vector<Point>& v)
{
	FileError retVal = FileError(ACCESS_DENIED);

	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (openMode & fstream::out)
	{
		ostringstream strs;
		Point tmp;
		for (int i = 0; i < v.size(); i++)
		{
			tmp = v[i];
			strs << tmp.x << " " << tmp.y << " " << tmp.z << " "<<endl;
			string str = strs.str();
			file << (str);
		}
		retVal = FileError(SUCCESS);
	}

	return retVal;
}

FileError CsvFile::Read(vector<Point>& v)
{
	FileError retVal = FileError(ACCESS_DENIED);
	file.seekg(0, file.end);
	int roz = file.tellg();
	file.seekg(0, file.beg);
	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (openMode & fstream::in)
	{
		v.clear();
		v.resize(roz / sizeof(Point));
		string line, num;
		vector<string> row;
		int i = 0;
		while (getline(file, line)) {
			row.clear();
			stringstream str(line);
			while (getline(str, num, ',')) {
				row.push_back(num);

			}
			if(row.size()==1)
			{
				v[i].x = stod(row[0]);
				v[i].y = 0;
				v[i].z = 0;
			}
			else if(row.size()==2)
			{
				v[i].x = stod(row[0]);
				v[i].y = stod(row[1]);
				v[i].z = 0;
			}
			else {
				v[i].x = stod(row[0]);
				v[i].y = stod(row[1]);
				v[i].z = stod(row[2]);
			}
			i++;
		}
		retVal = FileError(SUCCESS);
	}
		return retVal;
	}

FileError CsvFile::Read(Point & p, const unsigned long idx)
{
	FileError retVal = FileError(ACCESS_DENIED);
	file.seekg(0, file.end);
	int roz = file.tellg();
	file.seekg(0, file.beg);

	if (!file.is_open())
	{
		retVal = FileError(FILE_INVALID);
	}
	else if (idx * sizeof(Point) > roz)
	{
		retVal = FileError(OUT_OF_BOUNDS);
	}
	else if (openMode & fstream::in)
	{
		string tmp;
		for (int i = 0; i <= idx; i++) {
			getline(file, tmp);
		}
		vector<string> vek;
		vek = Split(tmp, ',');
		p.x =stod(vek[0]);
		p.y =stod(vek[1]);
		p.z =stod(vek[2]);

		retVal = FileError(SUCCESS);
	}

	return retVal;
}
