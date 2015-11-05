#include "PCH.h"
#include "PipelineManager.h"

#include "ShaderResoruceView.h"
#include "DepthStencilView.h"
#include "RenderTargetView.h"
#include "UnorderedAccessView.h"

#include <wincodec.h>
#include <sstream>

#include "ScreenGrab.h"		// ������SaveWICTextureToFile(...)

using namespace Sand;

PipelineManager::PipelineManager()
{

}

PipelineManager::~PipelineManager()
{
	if( m_pContext ) m_pContext->ClearState();
}

void PipelineManager::SetDeviceContext( DeviceContextComPtr pContext , D3D_FEATURE_LEVEL FeatureLevel )
{
	m_pContext = pContext;
	m_FeatureLevel = FeatureLevel;

	// �ɱ�̽׶�SetFeatureLevel


	// �̶��׶ε���SetFeatureLevel
	m_RasterizerStage.SetFeatureLevel( FeatureLevel );
	m_OutputMergeStage.SetFeatureLevel( FeatureLevel );
}

ID3D11DeviceContext* PipelineManager::GetDeviceContext()
{
	return m_pContext.Get();
}

void Sand::PipelineManager::ClearRenderTargets()
{
	m_OutputMergeStage.ClearDesiredState();
}

void Sand::PipelineManager::ApplyRenderTargets()
{
	// Ӧ�ø��º��Render Target View and Depth Stencil View
	m_OutputMergeStage.ApplyDesiredRenderTargetStates( m_pContext.Get() );
}

void Sand::PipelineManager::SaveTextureScreenShot( int ID , std::wstring filename )
{
	ID3D11Resource* pResource = Renderer::Get()->GetResourceByIndex( ID )->GetResource();

	if( pResource )
	{
		static int iScreenNum = 100000;
		iScreenNum++;

		std::wstringstream out;
		out << filename << iScreenNum << L".bmp";

		HRESULT hr = DirectX::SaveWICTextureToFile( m_pContext.Get() , pResource , GUID_ContainerFormatBmp , out.str().c_str() );
		// δ��ɣ�swapchain��Ӧ��buffer�����ȱ��������Դ������Ϊ0����˽�����Ϊ0��ͼ�񱣴浽fileǡ���ܴﵽ��ͼ������
	}
}

void PipelineManager::ClearBuffers( Vector4f& color , float depth , UINT stencil )
{
	ID3D11RenderTargetView* pRenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
	ID3D11DepthStencilState* pDepthStencilView = nullptr;

	int count = m_OutputMergeStage.GetCurrentState().RenderTargetViewCount.GetState();

	// --------------------------Clear Render Target View--------------------------------
	for( UINT i = 0; i < count; i++ )
	{
		// ��ȡÿ��render target view��index
		UINT index = m_OutputMergeStage.GetCurrentState().RenderTargetViews.GetState( i );
		// ��ȡRenderTargetView����
		RenderTargetView& RTV = Renderer::Get()->GetRenderTargetViewByIndex( index );

		pRenderTargetViews[i] = RTV.GetRenderTargetView();

		// ��������ɫ
		const float clearColors[] = { color.x , color.y , color.z , color.w };
		m_pContext->ClearRenderTargetView( pRenderTargetViews[i] , clearColors );
	}


	// ��ȡdepth stencil view��index
	UINT index = m_OutputMergeStage.GetCurrentState().DepthStencilViews.GetState();
	// ��ȡDepthStencilView����
	DepthStencilView& DSV = Renderer::Get()->GetDepthStencilViewByIndex( index );

	m_pContext->ClearDepthStencilView( DSV.Get() , D3D11_CLEAR_DEPTH || D3D11_CLEAR_STENCIL , depth , stencil );
}