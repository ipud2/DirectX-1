#ifndef ParameterContainer_h
#define ParameterContainer_h

#include "PCH.h"
#include "ConstantBufferParameterWriter.h"
#include "ShaderResourceParameterWriter.h"
#include "UnorderedAccessParameterWriter.h"
#include "SamplerParameterWriter.h"
#include "VectorParameterWriter.h"
#include "MatrixParameterWriter.h"
#include "MatrixArrayParameterWriter.h"

namespace Sand
{
	class ParameterContainer
	{
	public:
		ParameterContainer();
		virtual ~ParameterContainer();

		// 添加一个参数到container中
		void AddRenderParameter( ParameterWriter* pWriter );

		/*
		根据name获取ParameterWriter对象
		若存在，且类型符合，则将其返回
		否则返回nullptr
		*/
		ParameterWriter* GetRenderParameterWriter( const std::wstring& name );
		VectorParameterWriter* GetVectorParameterWriter( const std::wstring& name );
		MatrixParameterWriter* GetMatrixParameterWriter( const std::wstring& name );
		MatrixArrayParameterWriter* GetMatrixArrayParameterWriter( const std::wstring& name );
		UnorderedAccessParameterWriter* GetUnorderedAccessParameterWriter( const std::wstring& name );
		ShaderResourceParameterWriter* GetShaderResourceParameterWriter( const std::wstring& name );
		ConstantBufferParameterWriter* GetConstantBufferParameterWriter( const std::wstring& name );
		SamplerParameterWriter* GetSamplerParameterWriter( const std::wstring& name );

		/*
		功能：为指定名称的参数的Writer设置value
		name:参数名
		value:名字为name的参数的值

		method:
		根据name查询相应的ParameterWriter
		若不存在，则新建一个，并添加到Container中,然后初始化
		若已存在，则设置其Writer的value成员
		*/
		VectorParameterWriter* SetValueToVectorParameterWriter( const std::wstring& name , const Vector4f& Value );
		MatrixParameterWriter* SetValueToMatrixParameterWriter( const std::wstring& name , const Matrix4f& Value );
		MatrixArrayParameterWriter* SetValueToMatrixArrayParameterWriter( const std::wstring& name , Matrix4f* Value , int count );
		UnorderedAccessParameterWriter* SetValueToUnorderedAccessParameterWriter( const std::wstring& name , const ResourceProxyPtr& Value );
		ShaderResourceParameterWriter* SetValueToShaderResourceParameterWriter( const std::wstring& name , const ResourceProxyPtr& Value );
		ConstantBufferParameterWriter* SetValueToConstantBufferParameterWriter( const std::wstring& name , const ResourceProxyPtr& Value );
		SamplerParameterWriter* SetValueToSamplerParameterWriter( const std::wstring& name , int Value );



		/*
			功能：将Container中的所有Writer的value都应用到其Parameter上去
			即更新所有的渲染参数

			只有需要更新的数据才会创建ParameterWriter，并将其添加到Container中
			我们通过SetXXXParameter来设置相应参数值需要更新的值
			最后通过SetRenderParams将这些更新参数值应用到参数中
		*/
		void SetRenderParams( IParameterManager* pParameterManager );
		void InitRenderParams();

	protected:
		std::vector<ParameterWriter*> m_RenderParameter;
	};
}

#endif