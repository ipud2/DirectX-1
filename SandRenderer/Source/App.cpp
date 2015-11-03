#include "App.h"

using namespace Sand;

App AppInstance;

App::App()
{

}

App::~App()
{

}

bool App::ConfigureEngineComponents()
{
	m_width = 800;
	m_height = 600;

	m_bWindow = true;	// Ĭ�ϴ���ģʽ

	// ����Win32RenderWindow�������ڴ������ڣ������ô�����Ϣ
	m_pWindow = new Win32RenderWindow;
	m_pWindow->SetSize( m_width , m_height );
	m_pWindow->SetPosition( 100 , 100 );
	m_pWindow->SetCaption( GetName() );
	m_pWindow->Initialize( this );		// ��������

	
	// ������Ⱦ��

}

void App::ShutdownEngineComponents()
{

}

void App::Initialize()
{

}

void App::Update()
{

}

void App::Shutdown()
{

}

void App::TakeScreenShot()
{

}

bool App::HandleEvent( EventPtr pEvent )
{

}

std::wstring App::GetName()
{
	return std::wstring( L"SandRenderer" );
}