#ifndef Scene_h
#define Scene_h

#include "Node.h"
#include "Light.h"
#include "ParameterContainer.h"
#include "BaseCamera.h"

namespace Sand
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Update( float time );
		virtual void Render( Renderer* pRenderer );

		// ----------------Camera-----------------------
		void AddCamera( BaseCamera* camera );
		BaseCamera* GetCamera( unsigned int index );
		unsigned int GetCameraCount();

		// -----------------Light-----------------------
		void AddLight( Light* light );
		Light* GetLight( unsigned int index );
		unsigned int GetLightCount();

		// ------------------Actor----------------------
		void AddActor( Actor* actor );
		void RemoveActor( Actor* actor );

		// ----------------场景根节点---------------------
		Node* GetRootNode();
		
	protected:
		Node* m_pRootNode;
		std::vector< Light* > m_vLights;
		std::vector< BaseCamera* > m_vCameras;
		std::vector< Actor* > m_vActors;

	public:
		// paramter writers for the whole scene
		ParameterContainer SceneParameterWriters;
	};
};
#endif