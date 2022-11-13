#include "Producer.h"
using namespace std;
Producer::Producer()
{
	producer;
}
Producer::~Producer()
{
}
void Producer::ThreadRoutine() {
	while (isRunning())
	{
		double randItem = rand() % 100;
		mtx.lock();
		this->data.push_back(randItem);
		mtx.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));

	}
}

vector <double>Producer::GetData()
{
	mtx.lock();
	vector<double> outData = data;
	mtx.unlock();
	return outData;
}