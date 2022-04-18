#pragma once

class SpaghettiLog
{
	static SpaghettiLog *instance;
	int log_level = 0;

	SpaghettiLog() { };

public:
	static SpaghettiLog *GetInstance();
	
	void SetLogLevel(int level);
	
	void Log(const char* module_name, const char* message);   // Level 0
	void Warn(const char* module_name, const char* message);  // Level 1
	void Error(const char* module_name, const char* message); // Errors are always logged no matter what the log level is
};