#pragma once
#include "IThread.h"
#include"Producer.h"
using namespace std;
class Consumer : public IThread {
private:

	double _average{ 0 };
	Producer* _producer{ nullptr };
	mutex _mtx;
public:

	Consumer(Producer* producer);
	void ThreadRoutine() override;
	double GetAverage();



};