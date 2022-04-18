#include "String.h"

// Solution taken from https://stackoverflow.com/a/25385766/13160275

// trim from end of string (right)
std::string& StringUtils::rtrim(std::string& s, const char* t)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from beginning of string (left)
std::string& StringUtils::ltrim(std::string& s, const char* t)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from both ends of string (right then left)
std::string& StringUtils::trim(std::string& s, const char* t)
{
	return ltrim(rtrim(s, t), t);
}

bool StringUtils::IsInteger(const char* str)
{
	char* converted_value;
	long val = strtol(str, &converted_value, 10);

	return (*converted_value == NULL);
}
