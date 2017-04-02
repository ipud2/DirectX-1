#ifndef EDITOR_MANAGER_H
#define EDITOR_MANAGER_H

#include "SandGui.h"
#include "Engine/Base/TArray.h"

namespace Sand
{
	struct GuiConfig
	{
		SandGui EditorCallback;
		void* userdata;
	};

	class EditorManager
	{
	public:
		static EditorManager& Get();

		void RegisterEditor( SandGui _EditorCallback , void* _userdata );
		void UnRegisterEditor( SandGui _EditorCallback );

		void Update( ImGuiIO& io );

	protected:
		EditorManager();

	protected:
		TArray<GuiConfig> m_vGuiList;
	};
}
#endif