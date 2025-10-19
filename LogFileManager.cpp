#include "LogFileManager.h"
#include <chrono>


std::string LogFileManager::GetTimeStamp()
{
	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);

	std::tm local{};
	localtime_s(&local, &t);

	char buffer[32];
	std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", &local);
	return std::string(buffer);
}

LogFileManager::~LogFileManager()
{
	for (auto it = _logFilesMap.begin(); it != _logFilesMap.end(); ++it)
	{
		if (it->second && it->second->is_open())
		{
			it->second->close();
		}
	}
}
