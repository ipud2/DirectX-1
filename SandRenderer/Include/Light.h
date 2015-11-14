#ifndef Light_h
#define Light_h

#include "Actor.h"
#include "ParameterContainer.h"

namespace Sand
{
	class Light : public Actor
	{
	public:
		Light();
		virtual ~Light();

		void SetDiffuse( const Vector4f& Value );
		void SetSpecular( const Vector4f& Value );
		void SetAmbient( const Vector4f& Value );

	protected:
		VectorParameterWriter* m_DiffuseWriter;
		VectorParameterWriter* m_AmbientWriter;
		VectorParameterWriter* m_SpecularWriter;
	};
};
#endif