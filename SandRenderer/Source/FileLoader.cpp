#include "PCH.h"
#include "FileLoader.h"
#include "FileSystem.h"

using namespace Sand;

FileLoader::FileLoader()
{
	m_pData = nullptr;

	m_uiSize = 0;
}


FileLoader::~FileLoader()
{
	Close();
}

bool FileLoader::Open( const std::wstring& filename )
{ 
	// �رյ�ǰ�ѿ����ļ�
	Close();

	// --------------��ȡ�ļ����----------------------------
	HANDLE hFile = CreateFileW( filename.c_str() ,
								GENERIC_READ ,
								FILE_SHARE_READ ,
								nullptr ,
								OPEN_EXISTING ,
								FILE_ATTRIBUTE_NORMAL ,
								nullptr );

	if( INVALID_HANDLE_VALUE == hFile )
	{
		return false;
	}


	// ---------------------------��ȡLARGE_INTEGER�ṹ���ýṹ�����ڱ����ļ��ߴ�------------------------------
	LARGE_INTEGER FileSize = { 0 };

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
	FILE_STANDARD_INFO FileInfo;
	if( !GetFileInformationByHandleEx( hFile , FileStandardInfo , &FileInfo , sizeof( FileInfo ) ) )
	{
		CloseHandle( hFile );
		return nullptr;
	}

	FileSize = FileInfo.EndOfFile;
#else
	GetFileSizeEx( hFile , &FileSize );
#endif


	// ����32λ������˵���ļ����󣬾ܾ���ȡ
	if( FileSize.HighPart > 0 )
	{
		CloseHandle( hFile );
		return false;
	}

	m_uiSize = FileSize.LowPart;


	// ---------------------�������飬���ڱ����ļ�����----------------------------
	m_pData = new char[FileSize.LowPart];

	if( !m_pData )
	{
		CloseHandle( hFile );
		Close();
		return false;
	}

	DWORD BytesRead = 0;
	if( !ReadFile( hFile , m_pData , FileSize.LowPart , &BytesRead , nullptr ) )
	{
		CloseHandle( hFile );
		Close();
		return false;
	}

	CloseHandle( hFile );

	if( BytesRead < FileSize.LowPart )
	{
		Close();
		return false;
	}

	return true;
}

bool FileLoader::Close()
{
	if( nullptr != m_pData )
	{
		delete[] m_pData;
		m_pData = nullptr;
	}

	m_uiSize = 0;

	return true;
}

unsigned int FileLoader::GetDataSize()
{
	return m_uiSize;
}

char* FileLoader::GetDataPtr()
{
	return m_pData;
}