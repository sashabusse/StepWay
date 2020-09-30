#pragma once
#include <string>


namespace StepWay
{	namespace Utility
	{
	std::string Utf16ToUtf8(const std::wstring& wstr);
	
	std::wstring Utf8ToUtf16(const std::string& str);
	//in not valid conditions returns 0 (thats may be not the best way)
	char WChToCh(wchar_t wch);
	
	bool IsASCII(wchar_t wch);
}}