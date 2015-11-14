#include "PCH.h"
#include "ShaderFactory.h"
#include "Log.h"
#include "FileSystem.h"
#include "FileLoader.h"

using namespace Sand;

ShaderFactory::ShaderFactory()
{

}

ShaderFactory::~ShaderFactory()
{

}

ID3DBlob* ShaderFactory::GenerateShader( ShaderType type , std::wstring& Filename , std::wstring& Function , std::wstring& Model , const D3D_SHADER_MACRO* pDefines , bool EnableLogging )
{
	HRESULT hr = S_OK;

	std::wstringstream message;

	char AsciiFunction[1024];
	char AsciiModel[1024];

	// WideCharToMultiByte:映射一个Unicode 字符串到一个多字节字符串
	WideCharToMultiByte( CP_ACP , 0 , Function.c_str() , -1 , AsciiFunction , 1024 , NULL , NULL );
	WideCharToMultiByte( CP_ACP , 0 , Model.c_str() , -1 , AsciiModel , 1024 , NULL , NULL );

	UINT Flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
#ifndef _DEBUG
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	// ------------------构造文件路径------------------
	FileSystem FS;
	std::wstring& FilePath = FS.GetShaderFolder() + Filename;

	// -------------将shader文件加载到内存中--------------------
	FileLoader SourceFile;
	if( !SourceFile.Open( FilePath ) )
	{
		return nullptr;
	}

	// -----------------------编译shader文件----------------------------------
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrorMessage = nullptr;

	if( FAILED( hr = D3DCompile( SourceFile.GetDataPtr() ,
		SourceFile.GetDataSize() ,
		nullptr ,
		pDefines ,
		nullptr ,
		AsciiFunction ,
		AsciiModel ,
		Flags ,
		0 ,
		&pCompiledShader ,
		&pErrorMessage ) ) )
	{
		if( EnableLogging && ( pErrorMessage != nullptr ) )
		{
			LPVOID pCompileErrors = pErrorMessage->GetBufferPointer();
			const char* pMessage = ( const char* )pCompileErrors;
			message << SandString::ToUnicode( std::string( pMessage ) );
			Log::Get().Write( message.str().c_str() );
		}

		SAFE_RELEASE( pCompiledShader );
		SAFE_RELEASE( pErrorMessage );

		return nullptr;
	}

	SAFE_RELEASE( pErrorMessage );

	return pCompiledShader;
}