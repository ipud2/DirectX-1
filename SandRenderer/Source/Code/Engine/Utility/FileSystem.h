#ifndef FileSystem_h
#define FileSystem_h

#include <Engine/PCH.h>

/*
	用于获取资源目录
*/
class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	// Log目录
	std::wstring GetLogFolder();

	// 资源目录
	std::wstring GetDataFolder();
	std::wstring GetModelFolder();
	std::wstring GetShaderFolder();
	std::wstring GetTextureFolder();

	//************************************
	// Method:    FileExists
	// FullName:  Sand::FileSystem::FileExists
	// Access:    public 
	// Returns:   bool
	// Qualifier: 判断文件是否存在
	// Parameter: const std::wstring & file
	//************************************
	bool FileExists( const std::wstring& file );

	//************************************
	// Method:    FileIsNewer
	// FullName:  Sand::FileSystem::FileIsNewer
	// Access:    public 
	// Returns:   bool
	// Qualifier: 判断File1是否比File2更新
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