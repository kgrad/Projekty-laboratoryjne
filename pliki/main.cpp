#include "Point.h"
#include "IFIle.h"
#include "FileFactory.h"
#include <vector>
#include <iostream>
#include "Binaryfile.h"


using namespace std;

int main()
{
vector<Point> points;
Point punkt;
for (int i=0; i < 5; i++)
{
Point point(i, i+ 1.0, i+ 2.0);
points.push_back(point);
}

//plik zaczynamy od 0 wiersza

IFile* file1 = FileFactory::OpenFile("test.bin", "r");

//p1
file1->Read(points);
punkt = points[23];
cout << punkt.x << " " << punkt.y << " " << punkt.z << endl;


//p2
//file1->Read(punkt, 1);
//cout << punkt.x << " " << punkt.y << " " << punkt.z << endl;

//p3
//IFile* file1 = FileFactory::OpenFile("test.bin", "w");

//file1->Write(points);


IFile* file2 = FileFactory::OpenFile("test.csv", "r");


//p4
//file2->Read(points); //W linijce gdzie nie ma danej wspolrzednej, wypisywane s¹ zera   
//punkt = points[1];
//cout << punkt.x << " " << punkt.y << " " << punkt.z << endl;



//p5
file2->Read(punkt, 50);
cout << punkt.x << " " << punkt.y << " " << punkt.z << endl;



//IFile* file2= FileFactory::OpenFile("test.csv","w");
 
//p6
//file2->Write(points);



delete file1;
//delete file2; 
}