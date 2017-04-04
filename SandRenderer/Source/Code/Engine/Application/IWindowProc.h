#ifndef IWindowProc_h
#define IWindowProc_h

#include "Engine/PCH.h"

// ����Ϊ�ӿ��࣬����ָ��Ӧ�ó������ʵ�ֵĹ���
namespace Sand
{
	class IWindowProc
	{
	public:
		virtual LRESULT WindowProc( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam ) = 0;
		virtual void BeforeRegisterWindowClass( WNDCLASSEX& wc ) = 0;
	};
}

#endif