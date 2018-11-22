#ifndef LOGCONTAINER_H
#define LOGCONTAINER_H
#include <mutex>
#include <unordered_map>
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
	std::unordered_map<uint32_t, Log> Container;
public:
	int Register(const char*, uint32_t, uint32_t);
	int ForceFlush(uint32_t);
	int Unregister(uint32_t);
	int SomeAction();
	void Lock();
	void Unlock();
};

#endif // !LOGCONTAINER_H
