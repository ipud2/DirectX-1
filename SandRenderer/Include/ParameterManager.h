#ifndef ParameterManager_h
#define ParameterManager_h

#include "IParameterManager.h"

namespace Sand
{
	class ParameterManager : public IParameterManager
	{
	public:
		ParameterManager();
		virtual ~ParameterManager();

	public:
		// ----------------------------���ò���ֵ---------------------------------------
		// ����name���ò���ֵ
		virtual void SetVectorParameterData( const std::wstring& name , Vector4f* pVector );
		virtual void SetMatrixParameterData( const std::wstring& name , Matrix4f* pMatrix );
		virtual void SetMatrixArrayParameterData( const std::wstring& name , int count , Matrix4f* pMatrices );
		virtual void SetShaderResourceParameterData( const std::wstring& name , ResourceProxyPtr resource );
		virtual void SetUnorderedAccessParameterData( const std::wstring& name , ResourceProxyPtr resource , unsigned int initialize = -1 );
		virtual void SetConstantBufferParameterData( const std::wstring& name , ResourceProxyPtr resource );
		virtual void SetSamplerStateParameterData( const std::wstring& name , int* pID );

		// ����RenderParameterDX11���ò���ֵ
		virtual void SetVectorParameterData( RenderParameter* pParameter , Vector4f* pVector );
		virtual void SetMatrixParameterData( RenderParameter* pParameter , Matrix4f* pMatrix );
		virtual void SetMatrixArrayParameterData( RenderParameter* pParameter , Matrix4f* pMatrices );
		virtual void SetShaderResourceParameterData( RenderParameter* pParameter , ResourceProxyPtr resource );
		virtual void SetUnorderedAccessParameterData( RenderParameter* pParameter , ResourceProxyPtr resource );
		virtual void SetConstantBufferParameterData( RenderParameter* pParameter , ResourceProxyPtr resource );
		virtual void SetSamplerStateParameterData( RenderParameter* pParameter , int* pID );


	public:
		// ------------------------��ȡ��������---------------------------------------
		virtual RenderParameter* GetParameterRef( const std::wstring& name );
		virtual VectorParameter* GetVectorParameterRef( const std::wstring& name );
		virtual MatrixParameter* GetMatrixParameterRef( const std::wstring& name );
		virtual MatrixArrayParameter* GetMatrixArrayParameterRef( const std::wstring& name , int count );
		virtual ShaderResourceParameter* GetShaderResourceParameterRef( const std::wstring& name );
		virtual UnorderedAccessParameter* GetUnorderedAccessParameterRef( const std::wstring& name );
		virtual ConstantBufferParameter* GetConstantBufferParameterRef( const std::wstring& name );
		virtual SamplerParameter* GetSamplerStateParameterRef( const std::wstring& name );

	public:
		// ---------------------��ȡ����ֵ-----------------------------------
		virtual Vector4f GetVectorParameterData( const std::wstring& name );
		virtual Matrix4f GetMatrixParameterData( const std::wstring& name );
		virtual Matrix4f* GetMatrixArrayParameterData( const std::wstring& name , int count );
		virtual int GetUnorderedAccessParameterData( const std::wstring& name );
		virtual int GetShaderResourceParameterData( const std::wstring& name );
		virtual int GetConstantBufferParameterData( const std::wstring& name );
		virtual int GetSamplerStateParameterData( const std::wstring& name );

		virtual Vector4f GetVectorParameterData( RenderParameter* pParameter );
		virtual Matrix4f GetMatrixParameterData( RenderParameter* pParameter );
		virtual Matrix4f* GetMatrixArrayParameterData( RenderParameter* pParameter );
		virtual int GetShaderResourceParameterData( RenderParameter* pParameter );
		virtual int GetUnorderedAccessParameterData( RenderParameter* pParameter );
		virtual int GetSamplerStateParameterData( RenderParameter* pParameter );
		virtual int GetConstantBufferParameterData( RenderParameter* pParameter );

	public:
		virtual void SetWorldMatrixParameterData( Matrix4f* pMatrix );
		virtual void SetViewMatrixParameterData( Matrix4f* pMatrix );
		virtual void SetProjMatrixParameterData( Matrix4f* pMatrix );

	public:
		virtual void AttachParent( IParameterManager* pParent );
		virtual void DetachParent();

	protected:
		IParameterManager* m_pParent;

		MatrixParameter* m_pWorldMatrix;
		MatrixParameter* m_pViewMatrix;
		MatrixParameter* m_pProjMatrix;
		MatrixParameter* m_pWorldViewMatrix;
		MatrixParameter* m_pWorldProjMatrix;
		MatrixParameter* m_pViewProjMatrix;
		MatrixParameter* m_pWorldViewProjMatrix;

	private:
		static std::map<std::wstring , RenderParameter*> Parameters;
	};
}

#endif