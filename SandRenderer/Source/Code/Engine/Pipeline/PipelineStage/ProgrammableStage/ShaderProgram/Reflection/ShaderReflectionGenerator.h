#ifndef ShaderReflectionGenerator_h
#define ShaderReflectionGenerator_h

#include "Engine/Pipeline/PipelineStage/ProgrammableStage/ShaderProgram/Reflection/ShaderReflection.h"

namespace Sand
{
	class ShaderReflectionGenerator
	{
	public:
		// ConstantBuffer的name加上Filename，从而使得shader文件中的cbuffer的名字可以重复
		static ShaderReflection* GenerateReflection( ID3DBlob* pCompiledShader , std::wstring& Filename );

		~ShaderReflectionGenerator();

	private:
		// 无法构造ShaderReflectionGenerator对象
		// 因此我们唯一可以调用的只有ShaderReflectionGenerator::GenerateReflection()
		ShaderReflectionGenerator();
	};
};
#endif