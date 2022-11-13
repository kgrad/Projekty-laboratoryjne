#include "Integrator.h"
#include "IntegratorPool.h"
#include <vector>
#include <chrono>
#include <iostream>
#include "Producer.h";
#include "Consumer.h";
int main()
{
	//create dataset
	double dt = 0.1;
	std::vector<double> dataSet;
	for (size_t i = 0; i < 10000; i++)
	{
		dataSet.push_back(sin(i * dt) + 1);
		//dataSet.push_back(i);
	}

	//creating threads when needed (conventional way)
	{
		Integrator* integrators[100];
		auto tstart = std::chrono::high_resolution_clock::now();
		//create and start 100 threads
		for (size_t i = 0; i < 100; i++)
		{
			integrators[i] = new Integrator();
			integrators[i]->Start();
			integrators[i]->Count(dataSet, dt);
		}
		//wait until threads are done
		for (size_t i = 0; i < 100; i++)
		{
			while (integrators[i]->GetStatus() == Integrator::Status::WORKING);
			integrators[i]->Stop();
			delete integrators[i];
		}
		auto tstop = std::chrono::high_resolution_clock::now();
		std::cout << "Brak puli: " << std::chrono::duration_cast<std::chrono::microseconds>(tstop - tstart).count() << "us\n";

	}

	//pool
	{
		//create integrator pool with 10 workers
		auto threadPool = new IntegratorPool(100);
		auto tstart = std::chrono::high_resolution_clock::now();
		//perform count 100 times
		for (size_t i = 0; i < 100; i++)
		{
			Integrator* integrator;
			//blocking wait until any integrator is free
			while ((integrator = threadPool->GetInstance()) == nullptr);
			integrator->Count(dataSet, dt);
		}
		//wait until all threads are done
		while (threadPool->GetLoad() > 0);
		auto tstop = std::chrono::high_resolution_clock::now();
		std::cout << "Pula obiektow: " << std::chrono::duration_cast<std::chrono::microseconds>(tstop - tstart).count() << "us\n";
		delete threadPool;
	}
}


//dla dataSet=1000, i 10 w¹tków czasy:
/*
Brak puli: 1580745us
Pula obiektow: 172987us

*/

//dla dataSet=10, i 1 w¹tków czasy:
/*
Brak puli: 1431995us
Pula obiektow: 1555839us

*/

//dla dataSet=10000, i 100 w¹tków czasy:
/*
Brak puli: 1833054us
Pula obiektow: 23204us

*/