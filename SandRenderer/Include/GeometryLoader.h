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
	};
};
#endif