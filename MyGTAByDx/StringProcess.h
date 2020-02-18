#pragma once

#include <iostream>  
#include <windows.h>  
#include <string>  


class StringProcess
{
public:
	StringProcess();
	~StringProcess();

	char* WcharToChar(const wchar_t* wp);
	char* StringToChar(const std::string& s);
	char* WstringToChar(const std::wstring& ws);
	wchar_t* CharToWchar(const char* c);
	wchar_t* WstringToWchar(const std::wstring& ws);
	wchar_t* StringToWchar(const std::string& s);
	std::wstring StringToWstring(const std::string& s);
	std::string WstringToString(const std::wstring& ws);
	void Release();

private:

	char* m_char;
	wchar_t* m_wchar;
};

