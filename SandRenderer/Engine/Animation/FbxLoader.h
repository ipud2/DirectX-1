#ifndef FBX_LOADER_H
#define FBX_LOADER_H

namespace Sand
{
	class Geometry;

	namespace FbxLoader
	{
		Geometry* LoadFBX( const char* szFilename );
	}
}
#endif