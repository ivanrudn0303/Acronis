#include "LogContainer.h"
#include <ctime>
#include <iostream>


int LogContainer::Register(const char* path, uint32_t id, uint32_t UpdateTime)
{
	Lock();
	if ((!Container.empty()) && (Container.find(id) != Container.end()))
	{
		Unlock();
		return ERROR_EXIST_LOG;
	}
	Container[id]= {std::string(path), static_cast<uint32_t>(time(nullptr)) + UpdateTime, UpdateTime};
	Unlock();
	return 0;
}

int LogContainer::ForceFlush(uint32_t id)
{
	Lock();
	if (Container.empty())
	{
		Unlock();
		return ERROR_NO_LOG;
	}
	auto it = Container.find(id);
	if (it == Container.end())
	{
		Unlock();
		return ERROR_NO_LOG;
	}
	std::cout << "path: " << it->second.Path << "\ntime: " << it->second.UpdateTime << '\n';
	it->second.UpdateTime = it->second.Period + static_cast<uint32_t>(time(nullptr));
	Unlock();
	return 0;
}

int LogContainer::Unregister(uint32_t id)
{
	Lock();
	if(Container.empty())
	{
		Unlock();
		return ERROR_NO_LOG;
	}
	auto it = Container.find(id);
	if(it == Container.end())
	{
		Unlock();
		return ERROR_NO_LOG;
	}
	Container.erase(it);
	Unlock();
	return 0;
}

int LogContainer::SomeAction()
{
	Lock();
	uint32_t clock = static_cast<uint32_t>(time(nullptr));
	if (Container.empty())
	{
		Unlock();
		return 0;
	}
	for(auto it = Container.begin(); it != Container.cend(); ++it)
		if(clock > it->second.UpdateTime)
		{
			std::cout << "path: " << it->second.Path << "\ntime: " << it->second.UpdateTime << '\n';
			it->second.UpdateTime += it->second.Period;
		}
	Unlock();
	return 0;
}

void LogContainer::Lock()
{
	Mutex.lock();
}

void LogContainer::Unlock()
{
	Mutex.unlock();
}
