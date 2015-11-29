#ifndef BasicSurfaceProperty_h
#define BasicSurfaceProperty_h

#include "SurfaceProperty.h"

namespace Sand
{
	class BasicSurfaceProperty : public SurfaceProperty
	{
	public:
		BasicSurfaceProperty();
		virtual ~BasicSurfaceProperty();

		void SetSurfaceAmbientProperty( const Vector4f& value );
		void SetSurfaceDiffuseProperty( const Vector4f& value );
		void SetSurfaceSpecularProperty( const Vector4f& value );

	protected:
		VectorParameterWriter* m_pAmbientMaterialWriter;
		VectorParameterWriter* m_pDiffuseMaterialWriter;
		VectorParameterWriter* m_pSpecularMaterialWriter;
	};
}

#endif