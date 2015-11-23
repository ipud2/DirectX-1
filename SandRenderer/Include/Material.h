#ifndef Material_h
#define Material_h

#include "PCH.h"
#include "RenderEffect.h"
#include "Task.h"
#include "ParameterContainer.h"
#include "SceneRenderTask.h"

namespace Sand
{
	struct MaterialParams
	{
		bool bRender;
		RenderEffect* pEffect;
	};

	class Material
	{
	public:
		Material();
		virtual ~Material();

		void Update( float time );
		
		void SetRenderParams( IParameterManager* pParameterManager , VIEW_TYPE Type );

		void GetAllVertexShaderIDs( std::vector<int>& idList );

	public:
		MaterialParams Params[VT_NUM_VIEW_TYPES];

		// ������Ҫд�Ĳ���������Ҫ��Writer��������
		ParameterContainer Parameters;		
	};

	typedef std::shared_ptr<Material> MaterialPtr;
};
#endif