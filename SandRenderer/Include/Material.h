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

		// 所以需要写的参数都保存要给Writer对象在这
		ParameterContainer Parameters;		
	};

	typedef std::shared_ptr<Material> MaterialPtr;
};
#endif