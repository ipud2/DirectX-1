#ifndef ShaderReflectionGenerator_h
#define ShaderReflectionGenerator_h

#include "ShaderReflection.h"

namespace Sand
{
	class ShaderReflectionGenerator
	{
	public:
		static ShaderReflection* GenerateReflection( ID3DBlob* pCompiledShader );

		~ShaderReflectionGenerator();

	private:
		// 无法构造ShaderReflectionGenerator对象
		// 因此我们唯一可以调用的只有ShaderReflectionGenerator::GenerateReflection()
		ShaderReflectionGenerator();
	};
}
#endif