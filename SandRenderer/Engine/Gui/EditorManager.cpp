#include "PCH.h"
#include "EditorManager.h"

using namespace Sand;

EditorManager::EditorManager()
{
	m_vGuiList.Clear();
}

EditorManager& EditorManager::Get()
{
	static EditorManager editor_manager;
	return editor_manager;
}

void EditorManager::RegisterEditor( SandGui _EditorCallback , void* _userdata )
{
	/*m_vGuiList.Push( GuiConfig() );
	GuiConfig& config		= m_vGuiList.Back();
	config.EditorCallback	= _EditorCallback;
	config.userdata			= _userdata;*/
}

void EditorManager::UnRegisterEditor( SandGui _EditorCallback )
{
	int index = -1;
	for( int i = 0; i < m_vGuiList.GetSize(); i++ )
	{
		if( m_vGuiList[i].EditorCallback == _EditorCallback )
		{
			index = i;
		}
	}

	if( index != -1 )	m_vGuiList.Remove( index );
}

void EditorManager::Update( ImGuiIO& io )
{
	for( int i = 0; i < m_vGuiList.GetSize(); i++ )
	{
		m_vGuiList[i].EditorCallback( io , m_vGuiList[i].userdata );
	}
}