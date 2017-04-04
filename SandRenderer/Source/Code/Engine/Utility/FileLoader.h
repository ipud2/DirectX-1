#ifndef FileLoader_h
#define FileLoader_h

#include <Engine/PCH.h>

namespace Sand
{
	class FileLoader
	{
	public:
		FileLoader();
		~FileLoader();

		/*
			���ļ��������ļ���С����ȡ�ļ�����
		*/
		bool Open( const std::wstring& Filename );
		bool Close();

		char* GetDataPtr();
		unsigned int GetDataSize();

	protected:
		char* m_pData;
		unsigned int m_uiSize;
	};
}
#endif