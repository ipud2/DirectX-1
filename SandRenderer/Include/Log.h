#ifndef Log_h
#define Log_h

#include "PCH.h"

namespace Sand
{
	class Log
	{
	protected:
		Log();

		// 宽字符的输出流类对象
		std::wofstream LogFile;

	public:
		static Log& Get();

		//************************************
		// Method:    Open
		// FullName:  Sand::Log::Open
		// Access:    public 
		// Returns:   void
		// Qualifier: 打开Log文件，以便写入数据
		//************************************
		void Open();

		//************************************
		// Method:    Close
		// FullName:  Sand::Log::Close
		// Access:    public 
		// Returns:   void
		// Qualifier: 关闭Log文件，在应用程序终止时调用
		//************************************
		void Close();
		
		//************************************
		// Method:    Write
		// FullName:  Sand::Log::Write
		// Access:    public 
		// Returns:   void
		// Qualifier: 将字符串写入Log文件
		// Parameter: const wchar_t* TextString
		//************************************
		void Write( const wchar_t* TextString );

		//************************************
		// Method:    WriteSeparator
		// FullName:  Sand::Log::WriteSeparator
		// Access:    public 
		// Returns:   void
		// Qualifier: 在Log文件中写入分割线
		//************************************
		void WriteSeparator();
	};
}

#endif