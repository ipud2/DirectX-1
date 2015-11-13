#ifndef GeometryGenerator_h
#define GeometryGenerator_h

#include "Geometry.h"

namespace Sand
{
	class GeometryGenerator
	{
	public:
		/*
			生成全屏块
		*/
		static void GeneratorFullScreenQuad( GeometryPtr pGeometry );
		
		/*
			生成纹理平面
		*/
		static void GeneratorTexturedPlane( GeometryPtr pGeometry , int SizeX , int SizeY );
		
		/*
			生成球面
		*/
		static void GeneratorSphere( GeometryPtr pGeometry , unsigned int URes , unsigned int VRes , float Radius );

		/*
			生成坐标轴图元
		*/
		static void GeneratorAxisGeometry( GeometryPtr pGeometry );

	private:
		GeometryGenerator();
	};
};
#endif