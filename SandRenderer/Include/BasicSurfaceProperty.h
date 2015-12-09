#ifndef BasicSurfaceProperty_h
#define BasicSurfaceProperty_h

#include "SurfaceProperty.h"

namespace Sand
{
	struct BasicSurfacePropertyStructure
	{
		Vector4f AmbientMaterial;
		Vector4f DiffuseMaterial;
		Vector4f SpecularMaterial;

		Vector4f ReflectMaterial;
	};

	class BasicSurfaceProperty : public SurfaceProperty
	{
	public:
		BasicSurfaceProperty();
		virtual ~BasicSurfaceProperty();

		void SetSurfaceProperty( const Vector4f& AmbientMaterial , const Vector4f& DiffuseMaterial , const Vector4f& SpecularMaterial , const Vector4f& Reflect );

	protected:
		/*
			Êý¾ÝÖ¸Õë
		*/
		BasicSurfacePropertyStructure* m_pData;

		StructureParameterWriter* m_pSurfacePropertyStructureWriter;
	};
};
#endif