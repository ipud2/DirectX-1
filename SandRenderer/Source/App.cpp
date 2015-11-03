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

	m_bWindow = true;	// 默认窗口模式

	// 创建Win32RenderWindow对象，用于创建窗口，并设置窗口信息
	m_pWindow = new Win32RenderWindow;
	m_pWindow->SetSize( m_width , m_height );
	m_pWindow->SetPosition( 100 , 100 );
	m_pWindow->SetCaption( GetName() );
	m_pWindow->Initialize( this );		// 创建窗口

	
	// 配置渲染器

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