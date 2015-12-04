#include "PCH.h"
#include "Vector2fParameterWriter.h"

using namespace Sand;

Vector2fParameterWriter::Vector2fParameterWriter()
	:m_Value( 0.0f , 0.0f )
{

}

Vector2fParameterWriter::~Vector2fParameterWriter()
{

}

RenderParameter* Vector2fParameterWriter::GetRenderParameterRef()
{
	return m_pParameter;
}

void Vector2fParameterWriter::InitializeParameter()
{
	// 将当前的值设置到参数对象中
	m_pParameter->SetParameterData( &m_Value );
}

void Vector2fParameterWriter::UpdateValueToParameter( IParameterManager* pParamMgr )
{
	pParamMgr->SetVector2fParameterData( m_pParameter , &m_Value );
}

void Vector2fParameterWriter::SetValue( const Vector2f& Value )
{
	m_Value = Value;
}

Vector2f Vector2fParameterWriter::GetValue()
{
	return m_Value;
}

void Vector2fParameterWriter::SetRenderParameterRef( Vector2fParameter* pParam )
{
	m_pParameter = pParam;
}