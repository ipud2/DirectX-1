#ifndef Entity_h
#define Entity_h

#include "Transform.h"
#include "IController.h"
#include "Renderer.h"
#include "Renderable.h"

namespace Sand
{
	class Node;

	class Entity
	{
	public:
		Entity();
		~Entity();
		
		// 空间相关数据与功能
		void Update( float time );
		
		void Render(PipelineManager* pPipelineManager, IParameterManager* pParamManager, VIEW_TYPE View);

	public:
		void AttachParent( Node* pParent );
		void DetachParent();
		Node* GetParent();

	protected:
		void SetRenderParams(IParameterManager* pParameterManager);

	public:
		std::wstring GetName();
		void SetName( std::wstring name );

	protected:
		void UpdateLocal(float time);
		void UpdateWorld();

	protected:
		std::wstring m_Name;

		// 父节点
		Node* m_Parent;

		// 用于控制物体变换
		Transform m_Transform;

		// 使得物体拥有多个Controller
		ControllerPack<Entity> m_Controllers;

		Renderable Visual;

		ParameterContainer m_EntityParameterWriters;

		// Obtain Class Data Member Object Reference
	public:
		ControllerPack<Entity>& GetControllersRef();

		Renderable& GetRenderableRef();

		ParameterContainer& GetParameterWritersRef();

		Transform& GetTransformRef();
	};
};
#endif