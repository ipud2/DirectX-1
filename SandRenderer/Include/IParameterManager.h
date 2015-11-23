#ifndef IParameterManager_h
#define IParameterManager_h

#include "Renderer.h"
#include "VectorParameter.h"
#include "MatrixParameter.h"
#include "MatrixArrayParameter.h"
#include "ConstantBufferParameter.h"
#include "SamplerParameter.h"
#include "ShaderResourceParameter.h"
#include "UnorderedAccessParameter.h"

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
		virtual void SetVectorParameterData( const std::wstring& name , Vector4f* pVector ) = 0;
		virtual void SetMatrixParameterData( const std::wstring& name , Matrix4f* pMatrix ) = 0;
		virtual void SetMatrixArrayParameterData( const std::wstring& name , int count , Matrix4f* pMatrices ) = 0;
		virtual void SetShaderResourceParameterData( const std::wstring& name , ResourceProxyPtr resource ) = 0;
		virtual void SetUnorderedAccessParameterData( const std::wstring& name , ResourceProxyPtr reosurce , unsigned int initialize = -1 ) = 0;
		virtual void SetConstantBufferParameterData( const std::wstring& name , ResourceProxyPtr resource ) = 0;
		virtual void SetSamplerStateParameterData( const std::wstring& name , int* pID ) = 0;

		// 根据RenderParameterDX11设置参数值
		virtual void SetVectorParameterData( RenderParameter* pParameter , Vector4f* pVector ) = 0;
		virtual void SetMatrixParameterData( RenderParameter* pParameter , Matrix4f* pMatrix ) = 0;
		virtual void SetMatrixArrayParameterData( RenderParameter* pParameter , Matrix4f* pMatrices ) = 0;
		virtual void SetShaderResourceParameterData( RenderParameter* pParameter , ResourceProxyPtr resource ) = 0;
		virtual void SetUnorderedAccessParameterData( RenderParameter* pParameter , ResourceProxyPtr resource ) = 0;
		virtual void SetConstantBufferParameterData( RenderParameter* pParameter , ResourceProxyPtr resource ) = 0;
		virtual void SetSamplerStateParameterData( RenderParameter* pParameter , int* pID ) = 0;


		// ---------------------------------------------------获取参数对象---------------------------------------------------------------------
		// 根据name获取RenderParameterDX11对象
		virtual RenderParameter* GetParameterRef( const std::wstring& name ) = 0;
		virtual VectorParameter* GetVectorParameterRef( const std::wstring& name ) = 0;
		virtual MatrixParameter* GetMatrixParameterRef( const std::wstring& name ) = 0;
		virtual MatrixArrayParameter* GetMatrixArrayParameterRef( const std::wstring& name , int count ) = 0;
		virtual ShaderResourceParameter* GetShaderResourceParameterRef( const std::wstring& name ) = 0;
		virtual UnorderedAccessParameter* GetUnorderedAccessParameterRef( const std::wstring& name ) = 0;
		virtual ConstantBufferParameter* GetConstantBufferParameterRef( const std::wstring& name ) = 0;
		virtual SamplerParameter* GetSamplerStateParameterRef( const std::wstring& name ) = 0;

		// --------------------------------------------获取参数值-----------------------------------------------------------------------------------------
		virtual Vector4f GetVectorParameterData( const std::wstring& name ) = 0;
		virtual Matrix4f GetMatrixParameterData( const std::wstring& name ) = 0;
		virtual Matrix4f* GetMatrixArrayParameterData( const std::wstring& name , int count ) = 0;
		virtual int GetUnorderedAccessParameterData( const std::wstring& name ) = 0;
		virtual int GetShaderResourceParameterData( const std::wstring& name ) = 0;
		virtual int GetConstantBufferParameterData( const std::wstring& name ) = 0;
		virtual int GetSamplerStateParameterData( const std::wstring& name ) = 0;

		virtual Vector4f GetVectorParameterData( RenderParameter* pParameter ) = 0;
		virtual Matrix4f GetMatrixParameterData( RenderParameter* pParameter ) = 0;
		virtual Matrix4f* GetMatrixArrayParameterData( RenderParameter* pParameter ) = 0;
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