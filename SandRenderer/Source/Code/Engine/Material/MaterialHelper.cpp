#include <Engine/PCH.h>
#include "MaterialHelper.h"

std::string GetMatPath( const char* name )
{
	char path[1024];
	memset( path , 0 , sizeof( char ) * 1024 );
	sprintf_s( path , "../Data/Material/%s" , name );
	return path;
}