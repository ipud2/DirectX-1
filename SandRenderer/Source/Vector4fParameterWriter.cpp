#include "PCH.h"
#include "Vector4fParameterWriter.h"

using namespace Sand;

Vector4fParameterWriter::Vector4fParameterWriter()
	:m_Value( 0.0f , 0.0f , 0.0f , 0.0f )
{

}

Vector4fParameterWriter::~Vector4fParameterWriter()
{

}

RenderParameter* Vector4fParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void Vector4fParameterWriter::InitializeParameter()
{
	// 将当前的值设置到参数对象中
	m_pParameter->SetParameterData( &m_Value );
}

void Vector4fParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetVector4fParameterData( m_pParameter , &m_Value );
}

void Vector4fParameterWriter::SetValue( const Vector4f& Value )
{
	m_Value = Value;
}

Vector4f Vector4fParameterWriter::GetValue()
{
	return m_Value;
}

void Vector4fParameterWriter::SetRenderParameterRef( Vector4fParameter* pParam )
{
	m_pParameter = pParam;
}