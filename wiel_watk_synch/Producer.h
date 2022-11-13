#pragma once
#include "IThread.h"
#include <vector>
#include <mutex>
#include <iostream>
#include <chrono> 

using namespace std;
class Producer :public IThread {
private:
	mutex producer;
	mutex mtx;
	vector<double> data;

public:
	Producer();
	~Producer();
	void ThreadRoutine();
	vector<double> GetData();

};