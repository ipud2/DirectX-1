#ifndef EffectGenerator_h
#define EffectGenerator_h

#include "Effect.h"

namespace Sand
{
	class EffectGenerator
	{
	public:
		static EffectPtr GenerateWireFrame( Renderer& renderer );
		
		static EffectPtr GeneratePhong( Renderer& renderer );
		static EffectPtr GenerateSolidColor( Renderer& renderer );

		static EffectPtr GenerateFromFile( Renderer& renderer , std::wstring& filename , unsigned int shaders );

		static EffectPtr GenerateTexEffect( Renderer& renderer );

	private:
		EffectGenerator();
	};
}
#endif