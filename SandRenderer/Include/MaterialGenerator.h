#ifndef MaterialGenerator_h
#define MaterialGenerator_h

#include "Material.h"

namespace Sand
{
	class MaterialGenerator
	{
	public:
		static MaterialPtr GenerateWireFrame( Renderer& renderer );
		
		static MaterialPtr GeneratePhong( Renderer& renderer );
		static MaterialPtr GenerateSolidColor( Renderer& renderer );

		static MaterialPtr GenerateFromFile( Renderer& renderer , std::wstring& filename , unsigned int shaders );

		static MaterialPtr GenerateTexMaterial( Renderer& renderer );

	private:
		MaterialGenerator();
	};
}
#endif