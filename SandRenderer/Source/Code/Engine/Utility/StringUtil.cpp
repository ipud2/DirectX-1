#include <Engine/PCH.h>
#include "Engine/Utility/StringUtil.h"
#include <codecvt>
#include <locale>

StringUtil::StringUtil()
{

}

std::string StringUtil::ToAscii( const std::wstring& input )
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t> , wchar_t>().to_bytes( input );
}

std::wstring StringUtil::ToUnicode( const std::string& input )
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t> , wchar_t>().from_bytes( input );
}