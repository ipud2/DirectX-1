#ifndef GeometryGenerator_h
#define GeometryGenerator_h

#include "Engine/Pipeline/PipelineStage/StageExecutor/InputAssember/Geometry.h"

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
		static GeometryPtr GeneratorSphere( unsigned int SliceCount , unsigned int StackCount , float Radius );

		/*
			生成坐标轴图元
		*/
		static void GeneratorAxisGeometry( GeometryPtr pGeometry );

		/*
			天空盒
		*/
		static GeometryPtr GeneratorSkyBox( unsigned int SliceCount , unsigned int StackCount , float Radius );

		/*
			Grid
		*/
		static GeometryPtr GeneratorGrid( float width , float depth , unsigned int m , unsigned int n );

		/*
			Cylinder
		*/
		static GeometryPtr GeneratorCylinder( float bottomRadius , float topRadius , float height , unsigned int sliceCount , unsigned int stackCount );

	private:
		GeometryGenerator();
	};
};
#endif