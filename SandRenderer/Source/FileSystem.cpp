#include "PCH.h"
#include "FileSystem.h"
#include <shlobj.h>

using namespace Sand;

std::wstring FileSystem::sDataFolder = L"../Data/";
std::wstring FileSystem::sModelSubFolder = L"Models/";
std::wstring FileSystem::sShaderSubFolder = L"Shaders/";
std::wstring FileSystem::sTextureSubFolder = L"Textures/";
std::wstring FileSystem::sLogSubFolder = L"Log/";


FileSystem::FileSystem()
{

}

FileSystem::~FileSystem()
{

}

std::wstring FileSystem::GetDataFolder()
{
	return ( sDataFolder );
}

std::wstring FileSystem::GetLogFolder()
{
	// �ú��������ھ�̬��Ա������ǰ���ã����ֻ��ֱ��д�ɳ���
	return L"../Data/Log/";
}

std::wstring FileSystem::GetModelFolder()
{
	return ( sDataFolder + sModelSubFolder );
}

std::wstring FileSystem::GetShaderFolder()
{
	return ( sDataFolder + sShaderSubFolder );
}

std::wstring FileSystem::GetTextureFolder()
{
	return ( sDataFolder + sTextureSubFolder );
}

bool FileSystem::FileExists( const std::wstring& file )
{
	DWORD dwAttribute = GetFileAttributes( file.c_str() );

	// ��������Ч���Ի���Ŀ¼�������
	return ( ( dwAttribute != INVALID_FILE_ATTRIBUTES ) && ( dwAttribute != FILE_ATTRIBUTE_DIRECTORY ) );
}

bool FileSystem::FileIsNewer( const std::wstring& file1 , const std::wstring& file2 )
{
	// ���������ļ��Ѿ�ȷ���Ǵ��ڵ�

	HANDLE handle1 = INVALID_HANDLE_VALUE;
	HANDLE handle2 = INVALID_HANDLE_VALUE;

	// ��ȡ�ļ����
	handle1 = CreateFileW( file1.c_str() ,
						  GENERIC_READ ,
						  FILE_SHARE_READ ,
						  nullptr ,
						  OPEN_EXISTING ,
						  FILE_ATTRIBUTE_NORMAL ,
						  nullptr );

	handle2 = CreateFileW( file2.c_str() ,
						   GENERIC_READ ,
						   FILE_SHARE_READ ,
						   nullptr ,
						   OPEN_EXISTING ,
						   FILE_ATTRIBUTE_NORMAL ,
						   nullptr );

	FILETIME FileTime1;
	FILETIME FileTime2;

	// ��ȡ�ļ�ʱ����Ϣ
	GetFileTime( handle1 , nullptr , nullptr , &FileTime1 );
	GetFileTime( handle2 , nullptr , nullptr , &FileTime2 );

	// �Ƚ�ʱ��
	if( FileTime1.dwHighDateTime > FileTime2.dwHighDateTime )
	{
		return true;
	}
	else if(FileTime1.dwHighDateTime == FileTime2.dwHighDateTime )
	{
		return ( FileTime1.dwLowDateTime > FileTime2.dwLowDateTime );
	}

	return false;
}

