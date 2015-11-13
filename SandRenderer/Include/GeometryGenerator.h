#ifndef GeometryGenerator_h
#define GeometryGenerator_h

#include "Geometry.h"

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
		static void GeneratorSphere( GeometryPtr pGeometry , unsigned int URes , unsigned int VRes , float Radius );

		/*
			����������ͼԪ
		*/
		static void GeneratorAxisGeometry( GeometryPtr pGeometry );

	private:
		GeometryGenerator();
	};
};
#endif