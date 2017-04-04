#ifndef Light_h
#define Light_h

#include "Engine/Object/Actor/Actor.h"
#include "Engine/Parameter/ParameterContainer.h"

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