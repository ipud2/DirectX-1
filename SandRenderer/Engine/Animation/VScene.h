#ifndef V_SCENE_H
#define V_SCENE_H

#include <vector>

namespace Sand
{
	class VMesh;
	class VMaterial;

	class VScene
	{
	public:
		int CreateMesh( EInputMask eInputMask );
		VMaterial& CreateMaterial();

		VMesh* GetMesh( int iMeshIndex );
		VMaterial& GetMaterial( int iMeshIndex );

		int GetMeshCount();
		int GetMaterialCount();

	public:
		std::vector<VMesh*> m_vMesh;
		std::vector<VMaterial*> m_vMaterial;
	};
}

#endif