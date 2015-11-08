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


	// һ��һ�еĶ�ȡ����
	std::string line;

	while( std::getline( fin , line ) )
	{
		std::stringstream lineStream( line );
		std::string token;
		std::vector<std::string> tokenList;

		// ��ÿ�а��տո�ָ��
		while( lineStream >> token )
		{
			tokenList.push_back( token );
		}

		if( tokenList.size() != 0 )
		{
			// ��������
			if( tokenList[0] == "v" )
			{

			}
		}
	}

}