#ifndef GeometryGenerator_h
#define GeometryGenerator_h

#include "Engine/Pipeline/PipelineStage/StageExecutor/InputAssember/Geometry.h"

namespace Sand
{
	class GeometryGenerator
	{
	public:
		/*
			����ȫ����
		*/
		static void GeneratorFullScreenQuad( GeometryPtr pGeometry );
		
		/*
			��������ƽ��
		*/
		static void GeneratorTexturedPlane( GeometryPtr pGeometry , int SizeX , int SizeY );
		
		/*
			��������
		*/
		static GeometryPtr GeneratorSphere( unsigned int SliceCount , unsigned int StackCount , float Radius );

		/*
			����������ͼԪ
		*/
		static void GeneratorAxisGeometry( GeometryPtr pGeometry );

		/*
			��պ�
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