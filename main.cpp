#include <iostream>
#include "LogFileManager.h"

int main()
{
    LogFileManager manager;

    manager.OpenLogFile("error.log");
    manager.OpenLogFile("debug.log");
    manager.OpenLogFile("info.log");

    manager.WriteLog("error.log", "Database connection failed");
    manager.WriteLog("debug.log", "User login attempt");
    manager.WriteLog("info.log", "Server started successfully");

    std::vector<std::string> errorLogs = manager.ReadLogs("error.log");
    if (!errorLogs.empty())
        std::cout << "errorLogs[0] = " << errorLogs[0] << "\n";

    return 0;
}