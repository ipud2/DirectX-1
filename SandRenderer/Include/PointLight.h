#ifndef PointLight_h
#define PointLight_h

#include "Light.h"

namespace Sand
{
	class PointLight : public Light
	{
	public:
		PointLight();
		virtual ~PointLight();

	protected:
		VectorParameterWriter* m_PositionWriter;
	};
}
#endif