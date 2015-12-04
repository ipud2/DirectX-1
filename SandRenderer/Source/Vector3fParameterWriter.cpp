#include "PCH.h"
#include "Vector3fParameterWriter.h"

using namespace Sand;

Vector3fParameterWriter::Vector3fParameterWriter()
	:m_Value( 0.0f , 0.0f , 0.0f )
{

}

Vector3fParameterWriter::~Vector3fParameterWriter()
{

}

RenderParameter* Vector3fParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void Vector3fParameterWriter::InitializeParameter()
{
	// ����ǰ��ֵ���õ�����������
	m_pParameter->SetParameterData( &m_Value );
}

void Vector3fParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetVector3fParameterData( m_pParameter , &m_Value );
}

void Vector3fParameterWriter::SetValue( const Vector3f& Value )
{
	m_Value = Value;
}

Vector3f Vector3fParameterWriter::GetValue()
{
	return m_Value;
}

void Vector3fParameterWriter::SetRenderParameterRef( Vector3fParameter* pParam )
{
	m_pParameter = pParam;
}