#include "IntegratorPool.h"
#include <algorithm>


IntegratorPool::IntegratorPool(const size_t poolSize)
{
	for (size_t i = 0; i < poolSize; i++)
	{
		pool.push_back(new Integrator());
		pool.back()->Start();
	}
}


IntegratorPool::~IntegratorPool()
{
	while (pool.size() > 0)
	{
		pool.back()->Stop();
		delete pool.back();
		pool.pop_back();
	}
}

bool IsIdle(Integrator * integrator) {
	return integrator->GetStatus() == Integrator::Status::IDLE;
}

Integrator * IntegratorPool::GetInstance()
{
	Integrator * instance = nullptr;
	auto found = std::find_if(pool.begin(), pool.end(), IsIdle);
	if (found != pool.end()) instance = *found;
	return instance;
}

size_t IntegratorPool::GetLoad()
{
	size_t load = 0;
	for (size_t i = 0; i < pool.size(); i++)
	{
		if (pool[i]->GetStatus() == Integrator::Status::WORKING) ++load;
	}
	return load;
}
