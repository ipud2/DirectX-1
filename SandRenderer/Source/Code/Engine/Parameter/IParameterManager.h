#ifndef IParameterManager_h
#define IParameterManager_h

#include "Engine/Render/DXGI/Renderer.h"
#include "Engine/Parameter/Parameters/Numeric/Scalar/BoolParameter.h"
#include "Engine/Parameter/Parameters/Numeric/Scalar/FloatParameter.h"
#include "Engine/Parameter/Parameters/Numeric/Vector/Vector4fParameter.h"
#include "Engine/Parameter/Parameters/Numeric/Vector/Vector3fParameter.h"
#include "Engine/Parameter/Parameters/Numeric/Vector/Vector2fParameter.h"
#include "Engine/Parameter/Parameters/Numeric/Matrix/MatrixParameter.h"
#include "Engine/Parameter/Parameters/Numeric/Matrix/MatrixArrayParameter.h"
#include "Engine/Parameter/Parameters/Object/ConstantBufferParameter.h"
#include "Engine/Parameter/Parameters/Object/SamplerParameter.h"
#include "Engine/Parameter/Parameters/Object/ShaderResourceParameter.h"
#include "Engine/Parameter/Parameters/Object/UnorderedAccessParameter.h"
#include "Engine/Parameter/Parameters/Struct/StructureParameter.h"

namespace Sand
{
	class IParameterManager
	{
	public:
		IParameterManager()
		{

		}

		virtual ~IParameterManager()
		{

		}

		// ----------------------------------------------------------设置参数值---------------------------------------------------------------------

		// 根据name设置参数值
		virtual void SetBoolParameterData( const std::wstring& name , bool* pBool ) = 0;
		virtual void SetFloatParameterData( const std::wstring& name , float* pFloat ) = 0;
		virtual void SetVector4fParameterData( const std::wstring& name , Vector4f* pVector ) = 0;
		virtual void SetVector3fParameterData( const std::wstring& name , Vector3f* pVector ) = 0;
		virtual void SetVector2fParameterData( const std::wstring& name , Vector2f* pVector ) = 0;
		virtual void SetMatrixParameterData( const std::wstring& name , Matrix4f* pMatrix ) = 0;
		virtual void SetMatrixArrayParameterData( const std::wstring& name , int count , Matrix4f* pMatrices ) = 0;
		virtual void SetStructureParameterData( const std::wstring& name , int size , char* pStructure ) = 0;
		virtual void SetShaderResourceParameterData( const std::wstring& name , ResourceProxyPtr resource ) = 0;
		virtual void SetUnorderedAccessParameterData( const std::wstring& name , ResourceProxyPtr reosurce , unsigned int initialize = -1 ) = 0;
		virtual void SetConstantBufferParameterData( const std::wstring& name , ResourceProxyPtr resource ) = 0;
		virtual void SetSamplerStateParameterData( const std::wstring& name , int* pID ) = 0;

		// 根据RenderParameterDX11设置参数值
		virtual void SetBoolParameterData( RenderParameter* pParameter , bool* pBool ) = 0;
		virtual void SetFloatParameterData( RenderParameter* pParameter , float* pFloat ) = 0;
		virtual void SetVector4fParameterData( RenderParameter* pParameter , Vector4f* pVector ) = 0;
		virtual void SetVector3fParameterData( RenderParameter* pParameter , Vector3f* pVector ) = 0;
		virtual void SetVector2fParameterData( RenderParameter* pParameter , Vector2f* pVector ) = 0;
		virtual void SetMatrixParameterData( RenderParameter* pParameter , Matrix4f* pMatrix ) = 0;
		virtual void SetMatrixArrayParameterData( RenderParameter* pParameter , Matrix4f* pMatrices ) = 0;
		virtual void SetStructureParameterData( RenderParameter* pParameters , char* pStructure ) = 0;
		virtual void SetShaderResourceParameterData( RenderParameter* pParameter , ResourceProxyPtr resource ) = 0;
		virtual void SetUnorderedAccessParameterData( RenderParameter* pParameter , ResourceProxyPtr resource ) = 0;
		virtual void SetConstantBufferParameterData( RenderParameter* pParameter , ResourceProxyPtr resource ) = 0;
		virtual void SetSamplerStateParameterData( RenderParameter* pParameter , int* pID ) = 0;


		// ---------------------------------------------------获取参数对象---------------------------------------------------------------------
		// 根据name获取RenderParameterDX11对象
		virtual RenderParameter* GetParameterRef( const std::wstring& name ) = 0;
		virtual BoolParameter* GetBoolParameterRef( const std::wstring& name ) = 0;
		virtual FloatParameter* GetFloatParameterRef( const std::wstring& name ) = 0;
		virtual Vector4fParameter* GetVector4fParameterRef( const std::wstring& name ) = 0;
		virtual Vector3fParameter* GetVector3fParameterRef( const std::wstring& name ) = 0;
		virtual Vector2fParameter* GetVector2fParameterRef( const std::wstring& name ) = 0;
		virtual MatrixParameter* GetMatrixParameterRef( const std::wstring& name ) = 0;
		virtual MatrixArrayParameter* GetMatrixArrayParameterRef( const std::wstring& name , int count ) = 0;
		virtual StructureParameter* GetStructureParameterRef( const std::wstring& name , int size ) = 0;
		virtual ShaderResourceParameter* GetShaderResourceParameterRef( const std::wstring& name ) = 0;
		virtual UnorderedAccessParameter* GetUnorderedAccessParameterRef( const std::wstring& name ) = 0;
		virtual ConstantBufferParameter* GetConstantBufferParameterRef( const std::wstring& name ) = 0;
		virtual SamplerParameter* GetSamplerStateParameterRef( const std::wstring& name ) = 0;

		// --------------------------------------------获取参数值-----------------------------------------------------------------------------------------
		virtual bool GetBoolParameterData( const std::wstring& name ) = 0;
		virtual float GetFloatParameterData( const std::wstring& name ) = 0;
		virtual Vector4f GetVector4fParameterData( const std::wstring& name ) = 0;
		virtual Vector3f GetVector3fParameterData( const std::wstring& name ) = 0;
		virtual Vector2f GetVector2fParameterData( const std::wstring& name ) = 0;
		virtual Matrix4f GetMatrixParameterData( const std::wstring& name ) = 0;
		virtual Matrix4f* GetMatrixArrayParameterData( const std::wstring& name , int count ) = 0;
		virtual char* GetStructureParameterData( const std::wstring& name , int size ) = 0;
		virtual int GetUnorderedAccessParameterData( const std::wstring& name ) = 0;
		virtual int GetShaderResourceParameterData( const std::wstring& name ) = 0;
		virtual int GetConstantBufferParameterData( const std::wstring& name ) = 0;
		virtual int GetSamplerStateParameterData( const std::wstring& name ) = 0;

		virtual bool GetBoolParameterData( RenderParameter* pParameter ) = 0;
		virtual float GetFloatParameterData( RenderParameter* pParameter ) = 0;
		virtual Vector4f GetVector4fParameterData( RenderParameter* pParameter ) = 0;
		virtual Vector3f GetVector3fParameterData( RenderParameter* pParameter ) = 0;
		virtual Vector2f GetVector2fParameterData( RenderParameter* pParameter ) = 0;
		virtual Matrix4f GetMatrixParameterData( RenderParameter* pParameter ) = 0;
		virtual Matrix4f* GetMatrixArrayParameterData( RenderParameter* pParameter ) = 0;
		virtual char* GetStructureParameterData( RenderParameter* pParameter ) = 0;
		virtual int GetShaderResourceParameterData( RenderParameter* pParameter ) = 0;
		virtual int GetUnorderedAccessParameterData( RenderParameter* pParameter ) = 0;
		virtual int GetSamplerStateParameterData( RenderParameter* pParameter ) = 0;
		virtual int GetConstantBufferParameterData( RenderParameter* pParameter ) = 0;


		// --------------------------------------------------常用参数-----------------------------------------------------------------
		virtual void SetWorldMatrixParameterData( Matrix4f* pMatrix ) = 0;
		virtual void SetViewMatrixParameterData( Matrix4f* pMatrix ) = 0;
		virtual void SetProjMatrixParameterData( Matrix4f* pMatrix ) = 0;

		virtual void AttachParent( IParameterManager* pParent ) = 0;
		virtual void DetachParent() = 0;
	};
};
#endif