#ifndef InputAssemblerStageExecutor_h
#define InputAssemblerStageExecutor_h

#include "PCH.h"

namespace Sand
{
	class PipelineManager;
	class ParameterManager;

	// 将Shader和InputLayout结合在一起
	struct InputLayoutKey
	{
		int ShaderID;
		int InputLayoutID;
	};

	class InputAssemblerStageExecutor
	{
	public:
		InputAssemblerStageExecutor();
		virtual ~InputAssemblerStageExecutor();

		virtual void Execute( PipelineManager* pPipelineManager , ParameterManager* pParameterManager ) = 0;

		virtual void GeneratorInputLayout( int ShaderID );

		virtual void SetInputElementsDesc( int count , D3D11_INPUT_ELEMENT_DESC* pInputElementsDesc );

		virtual int GetInputLayout( int ShaderID );

	protected:
		std::vector<D3D11_INPUT_ELEMENT_DESC> m_InputElementsDesc;
		std::map<int , InputLayoutKey*> m_InputLayouts;
	};

	typedef std::shared_ptr<InputAssemblerStageExecutor> InputAssemblerStageExecutorPtr;
};
#endif