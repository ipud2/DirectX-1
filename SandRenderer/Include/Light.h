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

		Vector4f GetDiffuse() const;
		Vector4f GetAmbient() const;
		Vector4f GetSpecular() const;

		ParameterContainer Parameters;

	protected:
		VectorParameterWriter* m_DiffuseWriter;
		VectorParameterWriter* m_AmbientWriter;
		VectorParameterWriter* m_SpecularWriter;

		// µ∆π‚Œª÷√
		VectorParameterWriter* m_PositionWriter;
	};
};
#endif