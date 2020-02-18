#include "StringProcess.h"

using namespace std;

StringProcess::StringProcess() :
	m_char(NULL), m_wchar(NULL)
{
}


StringProcess::~StringProcess()
{
	Release();
}

char* StringProcess::WcharToChar(const wchar_t* wp)
{
	Release();
	int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

char* StringProcess::StringToChar(const string& s)
{
	return const_cast<char*>(s.c_str());
}

char* StringProcess::WstringToChar(const wstring& ws)
{
	const wchar_t* wp = ws.c_str();
	return WcharToChar(wp);
}

wchar_t* StringProcess::CharToWchar(const char* c)
{
	Release();
	int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_wchar, len);
	m_wchar[len] = '\0';
	return m_wchar;
}

wchar_t* StringProcess::WstringToWchar(const wstring& ws)
{
	return const_cast<wchar_t*>(ws.c_str());
}

wchar_t* StringProcess::StringToWchar(const string& s)
{
	const char* p = s.c_str();
	return CharToWchar(p);
}

wstring StringProcess::StringToWstring(const string& s)
{
	wstring ws;
	wchar_t* wp = StringToWchar(s);
	ws.append(wp);
	return ws;
}

string StringProcess::WstringToString(const wstring& ws)
{
	string s;
	char* p = WstringToChar(ws);
	s.append(p);
	return s;
}

void StringProcess::Release()
{
	if (m_char)
	{
		delete m_char;
		m_char = NULL;
	}
	if (m_wchar)
	{
		delete m_wchar;
		m_wchar = NULL;
	}
}
