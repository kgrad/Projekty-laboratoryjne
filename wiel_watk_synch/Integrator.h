#pragma once

#include <vector>
#include <mutex>
#include "IThread.h"

using namespace std;
class Integrator: public IThread {
public:
	enum Status
	{
		IDLE,
		WORKING
	};
	Integrator();
	~Integrator();
	void Count(const vector<double>&, const double);
	Status GetStatus();
	double GetResult();
	Status status;
private:
	vector <double> data;
	double step;
	double result;
	mutex dataMutex;
	mutex statusMutex;
	mutex resultMutex;
	void SetStatus(Status);
	void ThreadRoutine();
};