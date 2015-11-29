#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "Light.h"

namespace Sand
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight();
		virtual ~DirectionalLight();

		void SetLightDirection( const Vector4f& value );

	protected:
		VectorParameterWriter* m_pLightDirectionWriter;
	};
};
#endif