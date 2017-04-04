#ifndef VMATERIAL_H
#define VMATERIAL_H

#include <Engine/Math/Vector3f.h>

namespace Sand
{
	class VMaterial
	{
	public:
		VMaterial();

		void SetMapName( const char* szFilename , EMapType eMapType );

		void SetAmbient( float r , float g , float b  );
		void SetEmissive( float r , float g , float b );
		void SetDiffuse( float r , float g , float b );

		Vector3f& GetAmbient();
		Vector3f GetAmbient() const;

		Vector3f& GetEmissive();
		Vector3f GetEmissive() const;

		Vector3f& GetDiffuse();
		Vector3f GetDiffuse() const;

		 const char* GetMapName( EMapType eMapType );

	public:
		std::string m_MapName[EMT_MAPNUM];
		Vector3f	m_Ambient;
		Vector3f	m_Emissive;
		Vector3f	m_Diffuse;
	};
}
#endif