#include "PCH.h"

#include "GeometryLoader.h"
#include "FileSystem.h"
#include "Log.h"
#include "OBJ.h"

using namespace Sand;

GeometryPtr GeometryLoader::LoadOBJ( std::wstring filename )
{
	FileSystem fs;
	filename = fs.GetModelFolder() + filename;

	std::ifstream fin( filename , std::ios::in );
	if( !fin.is_open() )
	{
		Log::Get().Write( L"open obj file failed!" );
		return nullptr;
	}


	// 一行一行的读取数据
	std::string line;

	while( std::getline( fin , line ) )
	{
		std::stringstream lineStream( line );
		std::string token;
		std::vector<std::string> tokenList;

		// 将每行按照空格分割开来
		while( lineStream >> token )
		{
			tokenList.push_back( token );
		}

		if( tokenList.size() != 0 )
		{
			// 顶点数据
			if( tokenList[0] == "v" )
			{

			}
		}
	}

}