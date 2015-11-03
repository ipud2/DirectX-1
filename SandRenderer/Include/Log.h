#ifndef Log_h
#define Log_h

#include "PCH.h"

namespace Sand
{
	class Log
	{
	protected:
		Log();

		// ���ַ�������������
		std::wofstream LogFile;

	public:
		static Log& Get();

		//************************************
		// Method:    Open
		// FullName:  Sand::Log::Open
		// Access:    public 
		// Returns:   void
		// Qualifier: ��Log�ļ����Ա�д������
		//************************************
		void Open();

		//************************************
		// Method:    Close
		// FullName:  Sand::Log::Close
		// Access:    public 
		// Returns:   void
		// Qualifier: �ر�Log�ļ�����Ӧ�ó�����ֹʱ����
		//************************************
		void Close();
		
		//************************************
		// Method:    Write
		// FullName:  Sand::Log::Write
		// Access:    public 
		// Returns:   void
		// Qualifier: ���ַ���д��Log�ļ�
		// Parameter: const wchar_t* TextString
		//************************************
		void Write( const wchar_t* TextString );

		//************************************
		// Method:    WriteSeparator
		// FullName:  Sand::Log::WriteSeparator
		// Access:    public 
		// Returns:   void
		// Qualifier: ��Log�ļ���д��ָ���
		//************************************
		void WriteSeparator();
	};
}

#endif