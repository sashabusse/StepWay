#include "StepWayPCH.h"
#include "Utility.h"

namespace StepWay
{	namespace Utility
	{
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::string Utf16ToUtf8(const std::wstring& wstr)
	{
		return converter.to_bytes(wstr);
	}

	std::wstring Utf8ToUtf16(const std::string& str)
	{
		return converter.from_bytes(str);
	}
	char WChToCh(wchar_t wch)
	{
		if (IsASCII(wch))return (char)wch;
		return 0;
	}
	bool IsASCII(wchar_t wch)
	{
		return ((wchar_t)0xFF00)&wch;
	}
}}