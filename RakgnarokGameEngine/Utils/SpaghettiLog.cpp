#include "SpaghettiLog.h"
#include <iostream>

SpaghettiLog* SpaghettiLog::instance = 0;

SpaghettiLog* SpaghettiLog::GetInstance()
{
    if (!instance)
    {
		instance = new SpaghettiLog();
    }
	
    return instance;
}

void SpaghettiLog::SetLogLevel(int level)
{
	log_level = level;
}

void SpaghettiLog::Log(const char* module_name, const char* message)
{
	if (log_level >= 0)
	{
		printf("%s; %s\n", module_name, message);
	}
}

void SpaghettiLog::Warn(const char* module_name, const char* message)
{
	if (log_level >= 1)
	{
		printf("WARNING: %s; %s\n", module_name, message);
	}
}

void SpaghettiLog::Error(const char* module_name, const char* message)
{
	printf("ERROR: %s; %s\n", module_name, message);
}
