#ifndef GeometryLoader_h
#define GeometryLoader_h

#include "Geometry.h"

namespace Sand
{
	/*
		����ָ����ʽ�ļ�����������֯Ϊ������Ҫ����ʽ
	*/
	class GeometryLoader
	{
	public:
		static GeometryPtr LoadOBJ( std::wstring filename );
	};
};
#endif