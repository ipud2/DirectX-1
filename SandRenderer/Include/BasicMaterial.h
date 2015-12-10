#ifndef BasicMaterial_h
#define BasicMaterial_h

#include "SurfaceMaterial.h"

namespace Sand
{
	struct BasicMaterialStructure
	{
		Vector4f AmbientMaterial;
		Vector4f DiffuseMaterial;
		Vector4f SpecularMaterial;

		Vector4f ReflectMaterial;
	};

	class BasicMaterial : public SurfaceMaterial
	{
	public:
		BasicMaterial();
		virtual ~BasicMaterial();

		void SetMaterialData( const Vector4f& AmbientMaterial , const Vector4f& DiffuseMaterial , const Vector4f& SpecularMaterial , const Vector4f& Reflect );

	protected:
		/*
			Êý¾ÝÖ¸Õë
		*/
		BasicMaterialStructure* m_pData;

		StructureParameterWriter* m_pMaterialWriter;
	};
};
#endif