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
			打开文件，计算文件大小，获取文件数据
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