#ifndef GeometryLoader_h
#define GeometryLoader_h

#include "Geometry.h"

namespace Sand
{
	/*
		加载指定格式文件，将数据组织为我们想要的形式
	*/
	class GeometryLoader
	{
	public:
		static GeometryPtr LoadOBJ( std::wstring filename );
		static GeometryPtr LoadMS3D( std::wstring filename );

	private:
		Vector3f ToVector3f( const std::vector<std::string>& tokens );
		Vector2f ToVector2f( const std::vector<std::string>& tokens );
	};
};
#endif