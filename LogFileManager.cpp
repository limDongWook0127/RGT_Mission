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

void LogFileManager::OpenLogFile(const std::string& filename)
{
	if (_logFilesMap.find(filename) != _logFilesMap.end())
		return;

	auto file = std::make_unique<std::ofstream>(filename, std::ios::app);
	if (file->is_open())
		_logFilesMap[filename] = std::move(file);
	else
		std::cerr << "(Fail) log file open: " << filename << "\n";
}

void LogFileManager::WriteLog(const std::string& filename, const std::string& message)
{
	auto it = _logFilesMap.find(filename);
	if (it == _logFilesMap.end() || !it->second || !it->second->is_open())
	{
		std::cerr << "Write Fail: file not open : " << filename << "\n";
		return;
	}
	*(it->second) << GetTimeStamp() << " " << message << "\n";
	it->second->flush();
}

std::vector<std::string> LogFileManager::ReadLogs(const std::string& filename)
{
	std::ifstream infile(filename);
	std::vector<std::string> logs;

	if (!infile.is_open())
	{
		std::cerr << "(Fail) readLogs: cannot open " << filename << "\n";
		return logs;
	}

	std::string line;
	while (std::getline(infile, line))
	{
		logs.push_back(line);
	}

	return logs;
}

void LogFileManager::CloseLogFile(const std::string& filename)
{
	auto it = _logFilesMap.find(filename);
	if (it != _logFilesMap.end() && it->second && it->second->is_open())
	{
		it->second->close();
		_logFilesMap.erase(it);
	}
}

