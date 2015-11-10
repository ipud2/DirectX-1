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
		// �޷�����ShaderReflectionGenerator����
		// �������Ψһ���Ե��õ�ֻ��ShaderReflectionGenerator::GenerateReflection()
		ShaderReflectionGenerator();
	};
}
#endif