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
		// ----------------------------设置参数值---------------------------------------
		// 根据name设置参数值
		virtual void SetVector4fParameterData( const std::wstring& name , Vector4f* pVector );
		virtual void SetVector3fParameterData( const std::wstring& name , Vector3f* pVector );
		virtual void SetVector2fParameterData( const std::wstring& name , Vector2f* pVector );
		virtual void SetMatrixParameterData( const std::wstring& name , Matrix4f* pMatrix );
		virtual void SetMatrixArrayParameterData( const std::wstring& name , int count , Matrix4f* pMatrices );
		virtual void SetStructureParameterData( const std::wstring& name , int size , char* pData );
		virtual void SetShaderResourceParameterData( const std::wstring& name , ResourceProxyPtr resource );
		virtual void SetUnorderedAccessParameterData( const std::wstring& name , ResourceProxyPtr resource , unsigned int initialize = -1 );
		virtual void SetConstantBufferParameterData( const std::wstring& name , ResourceProxyPtr resource );
		virtual void SetSamplerStateParameterData( const std::wstring& name , int* pID );

		// 根据RenderParameterDX11设置参数值
		virtual void SetVector4fParameterData( RenderParameter* pParameter , Vector4f* pVector );
		virtual void SetVector3fParameterData( RenderParameter* pParameter , Vector3f* pVector );
		virtual void SetVector2fParameterData( RenderParameter* pParameter , Vector2f* pVector );
		virtual void SetMatrixParameterData( RenderParameter* pParameter , Matrix4f* pMatrix );
		virtual void SetMatrixArrayParameterData( RenderParameter* pParameter , Matrix4f* pMatrices );
		virtual void SetStructureParameterData( RenderParameter* pParameters , char* pStructure );
		virtual void SetShaderResourceParameterData( RenderParameter* pParameter , ResourceProxyPtr resource );
		virtual void SetUnorderedAccessParameterData( RenderParameter* pParameter , ResourceProxyPtr resource );
		virtual void SetConstantBufferParameterData( RenderParameter* pParameter , ResourceProxyPtr resource );
		virtual void SetSamplerStateParameterData( RenderParameter* pParameter , int* pID );


	public:
		// ------------------------获取参数引用---------------------------------------
		virtual RenderParameter* GetParameterRef( const std::wstring& name );
		virtual Vector4fParameter* GetVector4fParameterRef( const std::wstring& name );
		virtual Vector3fParameter* GetVector3fParameterRef( const std::wstring& name );
		virtual Vector2fParameter* GetVector2fParameterRef( const std::wstring& name );
		virtual MatrixParameter* GetMatrixParameterRef( const std::wstring& name );
		virtual MatrixArrayParameter* GetMatrixArrayParameterRef( const std::wstring& name , int count );
		virtual StructureParameter* GetStructureParameterRef( const std::wstring& name , int size );
		virtual ShaderResourceParameter* GetShaderResourceParameterRef( const std::wstring& name );
		virtual UnorderedAccessParameter* GetUnorderedAccessParameterRef( const std::wstring& name );
		virtual ConstantBufferParameter* GetConstantBufferParameterRef( const std::wstring& name );
		virtual SamplerParameter* GetSamplerStateParameterRef( const std::wstring& name );

	public:
		// ---------------------获取参数值-----------------------------------
		virtual Vector4f GetVector4fParameterData( const std::wstring& name );
		virtual Vector3f GetVector3fParameterData( const std::wstring& name );
		virtual Vector2f GetVector2fParameterData( const std::wstring& name );
		virtual Matrix4f GetMatrixParameterData( const std::wstring& name );
		virtual Matrix4f* GetMatrixArrayParameterData( const std::wstring& name , int count );
		virtual char* GetStructureParameterData( const std::wstring& name , int size );
		virtual int GetUnorderedAccessParameterData( const std::wstring& name );
		virtual int GetShaderResourceParameterData( const std::wstring& name );
		virtual int GetConstantBufferParameterData( const std::wstring& name );
		virtual int GetSamplerStateParameterData( const std::wstring& name );

		virtual Vector4f GetVector4fParameterData( RenderParameter* pParameter );
		virtual Vector3f GetVector3fParameterData( RenderParameter* pParameter );
		virtual Vector2f GetVector2fParameterData( RenderParameter* pParameter );
		virtual Matrix4f GetMatrixParameterData( RenderParameter* pParameter );
		virtual Matrix4f* GetMatrixArrayParameterData( RenderParameter* pParameter );
		virtual char* GetStructureParameterData( RenderParameter* pParameter );
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
		MatrixParameter* m_pWorldInvTransposeMatrix;

	private:
		static std::map<std::wstring , RenderParameter*> Parameters;
	};
};
#endif