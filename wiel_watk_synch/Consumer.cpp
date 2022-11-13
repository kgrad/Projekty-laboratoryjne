#include "Consumer.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
Consumer::Consumer(Producer* producer)
{
	_producer = producer;
}

void Consumer::ThreadRoutine()
{
	while (isRunning()) {

		vector<double> data = _producer->GetData();
		
		if (data.size() == 0)
			continue;
		double average = accumulate(data.begin(), data.end(),0);
		average = average / data.size();

		_mtx.lock();
		_average = average;
		_mtx.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));

	}
}

double Consumer::GetAverage() {
	_mtx.lock();
	double outAverage = _average;
	_mtx.unlock();

	return outAverage;
}



