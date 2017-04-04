#ifndef Effect_h
#define Effect_h

#include <Engine/PCH.h>
#include "Engine/Effect/RenderEffect.h"
#include "Engine/Effect/Task/Task.h"
#include "Engine/Parameter/ParameterContainer.h"
#include "Engine/Effect/task/SceneRenderTask.h"

namespace Sand
{
	// ��ɫ����
	struct ShaderScheme
	{
		bool bRender;
		RenderEffect* pEffect;
	};

	class Effect
	{
	public:
		Effect();
		virtual ~Effect();

		void Update( float time );
		
		void SetRenderParams( IParameterManager* pParameterManager , VIEW_TYPE Type );

		void GetAllVertexShaderIDs( std::vector<int>& idList );

	public:
		ShaderScheme Schemes[VT_NUM_VIEW_TYPES];

		// ������Ҫд�Ĳ���������Ҫ��Writer��������
		ParameterContainer ParameterWriters;		
	};

	typedef std::shared_ptr<Effect> EffectPtr;
};
#endif