#include "PCH.h"
#include "Log.h"
#include "FileSystem.h"

using namespace Sand;

Log::Log()
{

}

Log& Log::Get()
{
	// 静态对象只创建一次
	static Log log;
	return log;
}

void Log::Open()
{
	FileSystem fs;
	// Log文件路径
	std::wstring FilePath = fs.GetLogFolder() + std::wstring( L"log.txt" );

	// 打开Log文件
	LogFile.open( FilePath.c_str() );

	// 写入打开信息
	Write( L"Log file opened" );
}

void Log::Close()
{
	Write( L"close Log File" );

	LogFile.close();
}

void Log::Write( const wchar_t* TextString )
{
	LogFile << TextString << "\n";

	/*LogFile.flush();*/
}

void Sand::Log::WriteSeparator()
{
	LogFile << L"------------------------------------------------------------------------------\n";

	/*LogFile.flush();*/
}
