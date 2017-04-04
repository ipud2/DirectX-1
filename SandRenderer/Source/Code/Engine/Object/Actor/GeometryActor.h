#ifndef GEOMETRY_ACTOR_H
#define GEOMETRY_ACTOR_H

#include "Engine/Object/Actor/Actor.h"

namespace Sand
{
	class GeometryActor : public Actor
	{
	public:
		GeometryActor();

		virtual ~GeometryActor();

		void AddVertex( const Vector3f& pos );
		void AddVertex( const Vector3f& pos , const Vector3f& color );
		void AddVertex( const Vector3f& pos , const Vector2f& texcoord );
		void AddVertex( const Vector3f& pos , const Vector4f& color , const Vector2f& texcoord );

		void AddVertex( const Vector3f& pos , const Vector3f& normal );
		void AddVertex( const Vector3f& pos , const Vector3f& normal , const Vector4f& color );
		void AddVertex( const Vector3f& pos , const Vector3f& normal , const Vector2f& texcoord );
		void AddVertex( const Vector3f& pos , const Vector3f& normal , const Vector4f& color , const Vector2f& texcoord );

		void AddIndices( const unsigned int index );
		void AddIndices( const unsigned int i1 , const unsigned int i2 );
		void AddIndices( const unsigned int i1 , const unsigned int i2 , const unsigned int i3 );

		void SetPrimitiveType( D3D11_PRIMITIVE_TOPOLOGY topology );

		void DrawLine( const Vector3f& p1 , const Vector3f& p2 );
		void DrawSphere( const Vector3f& center , float radius , unsigned stacks = 6 , unsigned int slices = 20 );
	};
}
#endif