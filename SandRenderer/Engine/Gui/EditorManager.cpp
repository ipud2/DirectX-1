#include "PCH.h"
#include "EditorManager.h"

using namespace Sand;

EditorManager::EditorManager()
{
	m_vGuiList.clear();
}

EditorManager& EditorManager::Get()
{
	static EditorManager editor_manager;
	return editor_manager;
}

void EditorManager::RegisterEditor( SandGui _EditorCallback , void* _userdata )
{
	m_vGuiList.push_back( GuiConfig() );
	GuiConfig& config		= m_vGuiList.back();
	config.EditorCallback	= _EditorCallback;
	config.userdata			= _userdata;
}

void EditorManager::UnRegisterEditor( SandGui _EditorCallback )
{

}