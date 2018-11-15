#include "LogContainer.h"
#include "ctime"

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
	for (auto it = Container.begin(); it != Container.end(); ++it)
		if (it->UpdateTime > Paste->UpdateTime)
		{
			std::swap(*Paste, *it);
			return 0;
		}
	return 0;
}

int LogContainer::Register(const char* path)
{
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
