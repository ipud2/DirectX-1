#include "App.h"
#include "Log.h"

#include <sstream>
#include <DirectXMath.h>

#include "PipelineManager.h"
#include "BlendStateConfig.h"
#include "DepthStencilStateConfig.h"
#include "BufferConfig.h"
#include "RasterizerStateConfig.h"
#include "SwapChainConfig.h"
#include "Texture2DConfig.h"

using namespace Sand;

struct Vertex
{
	DirectX::XMFLOAT4 Pos;
	DirectX::XMFLOAT4 Color;
};

App AppInstance;

App::App()
{

}

App::~App()
{

}

bool App::ConfigureEngineComponents()
{
	// 创建Win32RenderWindow对象，用于创建窗口，并设置窗口信息
	m_pWindow = new Win32RenderWindow;
	m_pWindow->SetSize( 1366 , 768 );
	m_pWindow->SetPosition( 100 , 100 );
	m_pWindow->SetCaption( GetName() );
	m_pWindow->Initialize( this );		// 创建窗口


	// 配置渲染器
	m_pRenderer = new Renderer;

	// 创建Device & DeviceContext
	// 配置默认的Rasterizer State 和 Blend State and DepthStencilState
	if( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_HARDWARE , D3D_FEATURE_LEVEL_11_0 ) )
	{
		Log::Get().Write( L"无法创建硬件设备，尝试创建reference设备" );

		if( !m_pRenderer->Initialize( D3D_DRIVER_TYPE_REFERENCE , D3D_FEATURE_LEVEL_11_0 ) )
		{
			// 指定窗口的显示状态， 这里指定为隐藏
			ShowWindow( m_pWindow->GetHandle() , SW_HIDE );
			MessageBox( m_pWindow->GetHandle() , L"无法创建硬件/软件Direct3D 11设备，程序将会终止" , L"SandRenderer" , MB_ICONEXCLAMATION | MB_SYSTEMMODAL );
			RequestTermination();

			return false;
		}

		m_pTimer->SetFixedTimeStep( 1.0f / 10.0f );
	}

	// 创建交换链
	SwapChainConfig config;
	config.SetWidth( m_pWindow->GetWidth() );
	config.SetHeight( m_pWindow->GetHeight() );
	config.SetOutputWindow( m_pWindow->GetHandle() );
	m_iSwapChain = m_pRenderer->CreateSwapChain( &config );
	m_pWindow->SetSwapChain( m_iSwapChain );

	// 保存一份渲染目标索引的拷贝
	m_pRenderTarget = m_pRenderer->GetSwapChainResource( m_iSwapChain );

	// 创建深度缓存，并为其生成深度模板视图
	Texture2DConfig DepthConfig;
	DepthConfig.SetDepthBuffer( m_pWindow->GetWidth() , m_pWindow->GetHeight() );
	m_pDepthStencilTarget = m_pRenderer->CreateTexture2D( &DepthConfig , nullptr );

	// 设置render target view 和 depth stencil view
	m_pRenderer->GetPipelineManagerRef()->ClearRenderTargets();
	m_pRenderer->GetPipelineManagerRef()->GetOutputMergeStageRef().DesiredState.RenderTargetViews.SetState( 0 , m_pRenderTarget->GetRenderTargetViewID() );
	m_pRenderer->GetPipelineManagerRef()->GetOutputMergeStageRef().DesiredState.DepthStencilViews.SetState( m_pDepthStencilTarget->GetDepthStencilViewID() );
	m_pRenderer->GetPipelineManagerRef()->ApplyRenderTargets();

	// 设置Viewport
	D3D11_VIEWPORT view_port;
	view_port.Width = m_pWindow->GetWidth();
	view_port.Height = m_pWindow->GetHeight();
	view_port.TopLeftX = 0.0f;
	view_port.TopLeftY = 0.0f;
	view_port.MinDepth = 0.0f;
	view_port.MaxDepth = 1.0f;


	int view_port_id = m_pRenderer->CreateViewPort( view_port );
	m_pRenderer->GetPipelineManagerRef()->GetRasterizerStageRef().DesiredState.ViewportCount.SetState( 1 );
	m_pRenderer->GetPipelineManagerRef()->GetRasterizerStageRef().DesiredState.Viewports.SetState( 0 , view_port_id );


	// ------------------------------------
	m_Effect.SetVertexShader( m_pRenderer->LoadShader( ST_VERTEX_SHADER , std::wstring( L"RotatingCube.hlsl" ) , std::wstring( L"VSMain" ) , std::wstring( L"vs_4_0" ) ) );
	m_Effect.SetGeometryShader( m_pRenderer->LoadShader( ST_GEOMETRY_SHADER , std::wstring( L"RotatingCube.hlsl" ) , std::wstring( L"GSMain" ) , std::wstring( L"gs_4_0" ) ) );
	m_Effect.SetPixelShader( m_pRenderer->LoadShader( ST_PIXEL_SHADER , std::wstring( L"RotatingCube.hlsl" ) , std::wstring( L"PSMain" ) , std::wstring( L"ps_4_0" ) ) );

	// Input Layout
	D3D11_INPUT_ELEMENT_DESC desc[] = 
	{
		{ "POSITION" , 0 , DXGI_FORMAT_R32G32B32A32_FLOAT , 0 , 0 , D3D11_INPUT_PER_VERTEX_DATA , 0 } , 
		{ "COLOR" , 0 , DXGI_FORMAT_R32G32B32A32_FLOAT , 0 , 16 , D3D11_INPUT_PER_VERTEX_DATA , 0 }
	};
	std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;
	Layout.push_back( desc[0] );
	Layout.push_back( desc[1] );
	m_InputLayout = m_pRenderer->CreateInputLayout( Layout , m_Effect.GetVertexShader() );
	if( m_InputLayout == -1 )
	{
		Log::Get().Write( L"Failed to create vertex layout" );
		assert( false );
	}

	return true;
}

void App::ShutdownEngineComponents()
{
	if( m_pRenderer )
	{
		m_pRenderer->Shutdown();
		delete m_pRenderer;
	}

	if( m_pWindow )
	{
		m_pWindow->Shutdown();
		delete m_pWindow;
	}
}

void App::Initialize()
{
	// ------------------------Vertex Buffer-------------------------
	{
		Vertex vertices[] =
		{
			{ DirectX::XMFLOAT4( -1.0f , 1.0f , -1.0f , 1.0f ) , DirectX::XMFLOAT4( 0.0f , 0.0f , 1.0f , 1.0f ) } ,
			{ DirectX::XMFLOAT4( 1.0f , 1.0f , -1.0f , 1.0f ) , DirectX::XMFLOAT4( 0.0f , 1.0f , 0.0f , 1.0f ) } ,
			{ DirectX::XMFLOAT4( 1.0f , 1.0f , 1.0f , 1.0f ) , DirectX::XMFLOAT4( 0.0f , 1.0f , 1.0f , 1.0f ) } ,
			{ DirectX::XMFLOAT4( -1.0f , 1.0f , 1.0f , 1.0f ) , DirectX::XMFLOAT4( 1.0f , 0.0f , 0.0f , 1.0f ) } ,
			{ DirectX::XMFLOAT4( -1.0f , -1.0f , -1.0f , 1.0f ) , DirectX::XMFLOAT4( 1.0f , 0.0f , 1.0f , 1.0f ) } ,
			{ DirectX::XMFLOAT4( 1.0f , -1.0f , -1.0f , 1.0f ) , DirectX::XMFLOAT4( 1.0f , 1.0f , 0.0f , 1.0f ) } ,
			{ DirectX::XMFLOAT4( 1.0f , -1.0f , 1.0f , 1.0f ) , DirectX::XMFLOAT4( 1.0f , 1.0f , 1.0f , 1.0f ) } ,
			{ DirectX::XMFLOAT4( -1.0f , -1.0f , 1.0f , 1.0f ) , DirectX::XMFLOAT4( 0.0f , 0.0f , 0.0f , 1.0f ) } ,
		};

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = reinterpret_cast< void* >( &vertices[0] );
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		BufferConfig VertexBufferConfig;
		VertexBufferConfig.SetDefaultVertexBuffer( 8 * sizeof( Vertex ) , false );
		m_pVertexBuffer = m_pRenderer->CreateVertexBuffer( &VertexBufferConfig , &data );
		if( m_pVertexBuffer->GetResourceID() == -1 )
		{
			Log::Get().Write( L"Failed to create Vertex Buffer" );
			assert( false );
		}
	}
	
	// ---------------------------------Index Buffer-----------------------
	{
		UINT indices[] =
		{
			// up
			3 , 1 , 0 ,
			2 , 1 , 3 ,

			// near
			0 , 5 , 4 ,
			1 , 5 , 0 ,

			// left
			3 , 4 , 7 ,
			0 , 4 , 3 ,

			// right
			1 , 6 , 5 ,
			2 , 6 , 1 ,

			// far
			2 , 7 , 6 ,
			3 , 7 , 2 ,

			// bottom
			6 , 4 , 5 ,
			7 , 4 , 6 ,
		};

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = reinterpret_cast< void* >( &indices[0] );
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		BufferConfig IndexBufferConfig;
		IndexBufferConfig.SetDefaultIndexBuffer( sizeof( UINT ) * 36 , false );
		
		m_pIndexBuffer = m_pRenderer->CreateIndexBuffer( &IndexBufferConfig , &data );
		if( m_pIndexBuffer->GetResourceID() == -1 )
		{
			Log::Get().Write( L"Failed to Create Index Buffer" );
			assert( false );
		}
	}


	// -------------------------------设置变换矩阵----------------------
	m_WorldMatrix = Matrix4f::Identity();

	DirectX::XMVECTOR Eye = DirectX::XMVectorSet( 0.0f , 1.0f , -5.0f , 0.0f );
	DirectX::XMVECTOR At = DirectX::XMVectorSet( 0.0f , 1.0f , 0.0f , 0.0f );
	DirectX::XMVECTOR Up = DirectX::XMVectorSet( 0.0f , 1.0f , 0.0f , 0.0f );
	
	m_ViewMatrix = *( ( Matrix4f* )&DirectX::XMMatrixLookAtLH( Eye , At , Up ) );

	m_ProjMatrix = *( ( Matrix4f* )&DirectX::XMMatrixPerspectiveFovLH( DirectX::XM_PIDIV2 , ( float )m_pWindow->GetWidth() / ( float )m_pWindow->GetHeight() , 0.01f , 100.0f ) );

	m_pRenderer->GetParameterManagerRef()->SetWorldMatrixParameterData( &m_WorldMatrix );
	m_pRenderer->GetParameterManagerRef()->SetViewMatrixParameterData( &m_ViewMatrix );
	m_pRenderer->GetParameterManagerRef()->SetProjMatrixParameterData( &m_ProjMatrix );
}

void App::Update()
{
	m_pTimer->Update();

	// 设置背景
	m_pRenderer->GetPipelineManagerRef()->ClearBuffers( Vector4f( 0.0f , 0.0f , 0.0f , 0.0f ) , 1.0f );


	// ---------------------------让物体自动旋转-------------------------------------------------
	static DWORD TimeStart = 0;
	static float t = 0.0f;
	DWORD TimeCurrent = GetTickCount();
	if( TimeStart == 0 )
	{
		TimeStart = TimeCurrent;
	}
	else
	{
		t = ( TimeCurrent - TimeStart ) / 1000.0f;
	}

	m_WorldMatrix = Matrix4f::RotationMatrixY( t ) * Matrix4f::RotationMatrixX( t );
	
	m_pRenderer->GetParameterManagerRef()->SetWorldMatrixParameterData( &m_WorldMatrix );

	// --------------------Render-----------------
	UINT Stride = sizeof( Vertex );
	m_pRenderer->GetPipelineManagerRef()->Draw( m_Effect , m_pVertexBuffer , m_pIndexBuffer , m_InputLayout , D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST , Stride , 36 , m_pRenderer->GetParameterManagerRef() );

	m_pRenderer->Present( m_pWindow->GetSwapChain() );
}

void App::Shutdown()
{
	/*std::wstringstream out;
	out << L"Max FPS: " << m_pTimer->MaxFramerate();
	Log::Get().Write( out.str().c_str() );*/
}

void App::TakeScreenShot()
{
	if( m_bSaveScreenShot )
	{
		m_bSaveScreenShot = false;
		m_pRenderer->GetPipelineManagerRef()->SaveTextureScreenShot( 0 , GetName() );
	}
}

bool App::HandleEvent( EventPtr pEvent )
{
	return Application::HandleEvent( pEvent );
}

std::wstring App::GetName()
{
	return std::wstring( L"RotateCube" );
}