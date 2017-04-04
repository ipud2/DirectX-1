#ifndef ShaderReflectionGenerator_h
#define ShaderReflectionGenerator_h

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Reflection/ShaderReflection.h"

namespace Sand
{
	class ShaderReflectionGenerator
	{
	public:
		// ConstantBuffer��name����Filename���Ӷ�ʹ��shader�ļ��е�cbuffer�����ֿ����ظ�
		static ShaderReflection* GenerateReflection( ID3DBlob* pCompiledShader , std::wstring& Filename );

		~ShaderReflectionGenerator();

	private:
		// �޷�����ShaderReflectionGenerator����
		// �������Ψһ���Ե��õ�ֻ��ShaderReflectionGenerator::GenerateReflection()
		ShaderReflectionGenerator();
	};
};
#endif