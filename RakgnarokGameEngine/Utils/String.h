#pragma once
#include <string>

namespace StringUtils
{
	std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v");
	std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v");
	std::string& trim(std::string& s, const char* t = " \t\n\r\f\v");
	bool IsInteger(const char* str);
}