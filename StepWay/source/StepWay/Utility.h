#pragma once
#include <string>


namespace StepWay
{	namespace Utility
	{
	std::string WStrToStr(const std::wstring& wstr);
	std::wstring StrToWstr(const std::string& str);
	//in not valid conditions returns 0 (thats may be not the best way)
	char WChToCh(wchar_t wch);
	
	bool IsASCII(wchar_t wch);
}}