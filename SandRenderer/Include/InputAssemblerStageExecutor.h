#ifndef InputAssemblerStageExecutor_h
#define InputAssemblerStageExecutor_h

#include "PCH.h"

namespace Sand
{
	class PipelineManager;
	class IParameterManager;

	// ��Shader��InputLayout�����һ��
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

		virtual void Execute( PipelineManager* pPipelineManager , IParameterManager* pParameterManager ) = 0;

		virtual void GenerateInputLayout( int ShaderID );

		virtual void SetInputElementsDesc( int count , D3D11_INPUT_ELEMENT_DESC* pInputElementsDesc );

		virtual int GetInputLayout( int ShaderID );

	protected:
		std::vector<D3D11_INPUT_ELEMENT_DESC> m_InputElementsDesc;
		std::map<int , InputLayoutKey*> m_InputLayouts;
	};

	typedef std::shared_ptr<InputAssemblerStageExecutor> InputAssemblerStageExecutorPtr;
};
#endif