#include "Log.h"
#include "FileSystem.h"

using namespace Sand;

Log::Log()
{

}

Log& Log::Get()
{
	// ��̬����ֻ����һ��
	static Log log;
	return log;
}

void Sand::Log::Open()
{
	FileSystem fs;
	// Log�ļ�·��
	std::wstring FilePath = fs.GetLogFolder() + L"\\Log.txt";

	// ��Log�ļ�
	LogFile.open( FilePath.c_str() );

	// д�����Ϣ
	Write( L"Log file opened" );
}

void Sand::Log::Close()
{
	Write( L"close Log File" );

	LogFile.close();
}

void Sand::Log::Write( const wchar_t* TextString )
{
	LogFile << TextString << "\n";

	LogFile.flush();
}

void Sand::Log::WriteSeparator()
{
	LogFile << L"------------------------------------------------------------------------------\n";

	LogFile.flush();
}
