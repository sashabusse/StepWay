#pragma once
#include <string>


namespace StepWay
{	namespace Utility
	{
	std::string WStrToStr(const std::wstring& wstr);
	std::wstring StrToWstr(const std::string& str);
	
	bool IsASCII(wchar_t wch);
}}