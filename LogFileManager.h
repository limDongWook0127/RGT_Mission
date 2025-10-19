#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <iostream>
class LogFileManager
{
private:
    std::unordered_map<std::string, std::unique_ptr<std::ofstream>> _logFilesMap;
    std::string GetTimeStamp();

public:
    LogFileManager() {};
    ~LogFileManager();

    LogFileManager(const LogFileManager&) = delete;
    LogFileManager& operator=(const LogFileManager&) = delete;

    LogFileManager(LogFileManager&&) noexcept = default;
    LogFileManager& operator=(LogFileManager&&) noexcept = default;

    void OpenLogFile(const std::string& filename);
    void WriteLog(const std::string& filename, const std::string& message);
    std::vector<std::string> ReadLogs(const std::string& filename);
    void CloseLogFile(const std::string& filename);
};
