#ifndef LOGCONTAINER_H
#define LOGCONTAINER_H
#include <mutex>
#include <list>
#include <string>
#include <cstdint>

#define ERROR_NO_LOG 1
#define ERROR_EXIST_LOG 4

struct Log
{
	std::string Path;
	uint32_t UpdateTime;
	uint32_t Period;
};

class LogContainer
{
private:
	std::mutex Mutex;
	std::list<Log> Container;
public:
	int Update(const char*, uint32_t);
	int Register(const char*);
	int Unregister(const char*);
	int SomeAction();
	void Lock();
	void Unlock();
};

#endif // !LOGCONTAINER_H
