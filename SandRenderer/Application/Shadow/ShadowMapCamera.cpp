#include "PCH.h"
#include "ShadowMapCamera.h"
#include "Renderer.h"

using namespace Sand;

ShadowMapCamera::ShadowMapCamera()
{
	m_pShadowTransformWriter = ParameterWriters.GetMatrixParameterWriter( L"ShadowTransformMatrix" );
}

ShadowMapCamera::~ShadowMapCamera()
{

}

void ShadowMapCamera::RenderFrame( Renderer* pRenderer )
{
	if ( m_pRenderView )
	{
		// ���ǿ��Զ�̬�޸���Ⱦ�ĳ���
		if ( m_pScene )
		{
			m_pRenderView->SetScene( m_pScene );
		}

		Matrix4f ViewMatrix = m_pRoot->GetTransformRef().GetView();
		// ������ͼ����
		m_pRenderView->SetViewMatrix( ViewMatrix );
		// ��������ͶӰ����
		SetOrthographicParams( ViewMatrix.GetTranslate() );

		/*
			����������ַ�ʽ������ΪShadowMap�ڴ���ϸ��ʱ����ҪMainCamera��ViewPosition
			���ֻ�����ⲿ����m_ViewPosition��Ȼ�󴫸�m_ViewPosition�����������������
		*/
		m_pViewPositionWriter->SetValue( m_ViewPosition );

		m_pShadowTransformWriter->SetValue( GetShadowTransformMatrix() );

		ParameterWriters.InitRenderParams();

		// ����Ⱦ��ͼ���������б���
		m_pRenderView->QueuePreTasks( pRenderer );

		// ִ������
		pRenderer->ProcessTaskQueue();
	}
}

void ShadowMapCamera::SetOrthographicParams( const Vector3f& SphereCenter )
{
	/*
		��ͶӰ������������ͼ���������Ҫÿ֡������
	*/
	float Left = SphereCenter.x - m_Radius;
	float Right = SphereCenter.x + m_Radius;
	float Bottom = SphereCenter.y - m_Radius;
	float Top = SphereCenter.y + m_Radius;
	float Near = SphereCenter.z - m_Radius;
	float Far = SphereCenter.z + m_Radius;

	float ReciprocalWidth = 1.0f / ( Right - Left );
	float ReciprocalHeight = 1.0f / ( Top - Bottom );
	float fRange = 1.0f / ( Far - Near );

	m_ProjMatrix[0] = ReciprocalWidth + ReciprocalWidth;
	m_ProjMatrix[1] = 0.0f;
	m_ProjMatrix[2] = 0.0f;
	m_ProjMatrix[3] = 0.0f;

	m_ProjMatrix[4] = 0.0f;
	m_ProjMatrix[5] = ReciprocalHeight + ReciprocalHeight;
	m_ProjMatrix[6] = 0.0f;
	m_ProjMatrix[7] = 0.0f;

	m_ProjMatrix[8] = 0.0f;
	m_ProjMatrix[9] = 0.0f;
	m_ProjMatrix[10] = fRange;
	m_ProjMatrix[11] = 0.0f;

	m_ProjMatrix[12] = -( Left + Right ) * ReciprocalWidth;
	m_ProjMatrix[13] = -( Top + Bottom ) * ReciprocalHeight;
	m_ProjMatrix[14] = -fRange * Near;
	m_ProjMatrix[15] = 1.0f;

	if ( m_pRenderView )
	{
		m_pRenderView->SetProjMatrix( m_ProjMatrix );
	}
}

Matrix4f ShadowMapCamera::GetShadowTransformMatrix() const
{
	/*
		�ú���Ӧ�����ڳ�����Ⱦ�����Ⱦ
	*/
	Matrix4f T
	(	0.5f , 0.0f , 0.0f , 0.0f ,
		0.0f , -0.5f , 0.0f , 0.0f ,
		0.0f , 0.0f , 1.0f , 0.0f ,
		0.5f , 0.5f , 0.0f , 1.0f 
	);

	return m_pRoot->GetTransformRef().GetView() * m_ProjMatrix * T;
}

void ShadowMapCamera::SetBoundSphereRadius( float Radius )
{
	m_Radius = Radius;
}