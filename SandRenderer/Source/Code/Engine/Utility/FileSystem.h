#ifndef FileSystem_h
#define FileSystem_h

#include <Engine/PCH.h>

/*
	���ڻ�ȡ��ԴĿ¼
*/
class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	// LogĿ¼
	std::wstring GetLogFolder();

	// ��ԴĿ¼
	std::wstring GetDataFolder();
	std::wstring GetModelFolder();
	std::wstring GetShaderFolder();
	std::wstring GetTextureFolder();

	//************************************
	// Method:    FileExists
	// FullName:  Sand::FileSystem::FileExists
	// Access:    public 
	// Returns:   bool
	// Qualifier: �ж��ļ��Ƿ����
	// Parameter: const std::wstring & file
	//************************************
	bool FileExists( const std::wstring& file );

	//************************************
	// Method:    FileIsNewer
	// FullName:  Sand::FileSystem::FileIsNewer
	// Access:    public 
	// Returns:   bool
	// Qualifier: �ж�File1�Ƿ��File2����
	// Parameter: const std::wstring & file1
	// Parameter: const std::wstring & file2
	//************************************
	bool FileIsNewer( const std::wstring& file1 , const std::wstring& file2 );

private:
	static std::wstring sDataFolder;
	static std::wstring sModelSubFolder;
	static std::wstring sShaderSubFolder;
	static std::wstring sTextureSubFolder;
	static std::wstring sLogSubFolder;
};

#endif