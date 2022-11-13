#include "Integrator.h"
using namespace std;
Integrator::Integrator()
{
	status = IDLE;
	step = 0;
	data.clear();
	result = 0;
}

Integrator::~Integrator()
{
	Stop();
}

void Integrator::Count(const vector<double>&data_l, const double dx)
{
	step = dx;
	statusMutex.lock();
	SetStatus(WORKING);
	statusMutex.unlock();

	dataMutex.lock();
	data = data_l;
	dataMutex.unlock();
}

Integrator::Status Integrator::GetStatus()
{
	return status;
}

double Integrator::GetResult()
{
	return result;
}



void Integrator::SetStatus(Status st)
{
	if (st == IDLE)
		status = IDLE;
	else status = WORKING;

}

void Integrator::ThreadRoutine()
{
	while (isRunning()) {

		if (GetStatus() == IDLE) {
			this_thread::sleep_for(chrono::milliseconds(1));
		}
		else {
			
			dataMutex.lock();
			
			int i = 0;
			resultMutex.lock();
			while (i<data.size()) {
				result += data[i]*step;
				i++;
			}

			dataMutex.unlock();
		
			resultMutex.unlock();

			statusMutex.lock();
			SetStatus(IDLE);
			statusMutex.unlock();

		}
		

	}
}
