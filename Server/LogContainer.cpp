#include "LogContainer.h"
#include <ctime>
#include <iostream>

std::list<Log>::iterator Find(std::list<Log>*, const char*);

int LogContainer::Update(const char* path, uint32_t period)
{
	if (Container.empty())
		return ERROR_NO_LOG;
	std::list<Log>::iterator Paste = Find(&Container, path);
	if (Paste == Container.end())
		return ERROR_NO_LOG;

	Paste->UpdateTime = period + static_cast<uint32_t>(time(nullptr));
	Paste->Period = period;
	return 0;
}

int LogContainer::Register(const char* path)
{
	if ((!Container.empty()) && (Find(&Container, path) != Container.end()))
		return ERROR_EXIST_LOG;
	Container.push_back({std::string(path), (uint32_t)(~0), (uint32_t)(~0)});
	return 0;
}

int LogContainer::Unregister(const char* path)
{
	if(Container.empty())
		return ERROR_NO_LOG;
	auto it = Find(&Container, path);
	if(it == Container.end())
		return ERROR_NO_LOG;
	Container.erase(it);
	return 0;
}

int LogContainer::SomeAction()
{
	uint32_t clock = static_cast<uint32_t>(time(nullptr));
	if (Container.empty())
		return 0;
	for(auto it = Container.begin(); it != Container.cend(); ++it)
		if(clock > it->UpdateTime)
		{
			std::cout << "path: " << it->Path << "\ntime: " << it->UpdateTime << '\n';
			it->UpdateTime += it->Period;
		}
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

std::list<Log>::iterator Find(std::list<Log>* List, const char *path)
{
	for (auto it = List->begin(); it != List->end(); ++it)
		if (it->Path == path)
			return it;
	return List->end();
}
