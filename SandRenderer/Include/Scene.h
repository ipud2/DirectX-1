#ifndef Scene_h
#define Scene_h

#include "Node.h"
namespace Sand
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		Node* GetRoot();
	protected:
		Node* m_pRoot;
	};
}

#endif