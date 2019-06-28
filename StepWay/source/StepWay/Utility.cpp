#include "StepWayPCH.h"
#include "Utility.h"

namespace StepWay
{	namespace Utility
	{
	static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	std::string WStrToStr(const std::wstring& wstr)
	{
		return converter.to_bytes(wstr);
	}

	std::wstring StrToWstr(const std::string& str)
	{
		return converter.from_bytes(str);
	}
}}