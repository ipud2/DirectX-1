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

		void UpdateRenderParams( IParameterManager* pParamMgr );

	protected:
		ParameterContainer m_LightParameterWriters;
	};
};
#endif