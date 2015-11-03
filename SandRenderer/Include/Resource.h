#ifndef Resource_h
#define Resource_h

#include "Renderer.h"

namespace Sand
{
	// 资源类的基类
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		virtual ResourceType GetType() = 0;
		virtual ID3D11Resource* GetResource() = 0;

		unsigned short GetInnerID();

		static unsigned short s_usResourceID;
		unsigned short m_usInnerID;
	};
};

#endif