#ifndef ParameterContainer_h
#define ParameterContainer_h

#include "PCH.h"
#include "ConstantBufferParameterWriter.h"
#include "ShaderResourceParameterWriter.h"
#include "UnorderedAccessParameterWriter.h"
#include "SamplerParameterWriter.h"
#include "Vector4fParameterWriter.h"
#include "Vector3fParameterWriter.h"
#include "Vector2fParameterWriter.h"
#include "MatrixParameterWriter.h"
#include "MatrixArrayParameterWriter.h"
#include "StructureParameterWriter.h"

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
			获取指定名字的ParameterWriter对象
			若不存在，则创建
		*/
		ParameterWriter* GetRenderParameterWriter( const std::wstring& name );
		Vector4fParameterWriter* GetVector4fParameterWriter( const std::wstring& name );
		Vector3fParameterWriter* GetVector3fParameterWriter( const std::wstring& name );
		Vector2fParameterWriter* GetVector2fParameterWriter( const std::wstring& name );
		MatrixParameterWriter* GetMatrixParameterWriter( const std::wstring& name );
		MatrixArrayParameterWriter* GetMatrixArrayParameterWriter( const std::wstring& name , int count );
		StructureParameterWriter* GetStructureParameterWriter( const std::wstring& name , int Size );
		UnorderedAccessParameterWriter* GetUnorderedAccessParameterWriter( const std::wstring& name );
		ShaderResourceParameterWriter* GetShaderResourceParameterWriter( const std::wstring& name );
		ConstantBufferParameterWriter* GetConstantBufferParameterWriter( const std::wstring& name );
		SamplerParameterWriter* GetSamplerParameterWriter( const std::wstring& name );

		/*
			功能：将Container中的所有Writer的value都应用到其Parameter上去
			即更新所有的渲染参数

			只有需要更新的数据才会创建ParameterWriter，并将其添加到Container中
			我们通过SetXXXParameter来设置相应参数值需要更新的值
			最后通过SetRenderParams将这些更新参数值应用到参数中
		*/
		void UpdateRenderParam( IParameterManager* pParameterManager );
		void InitRenderParams();

	protected:
		std::vector<ParameterWriter*> m_RenderParameter;
	};
}

#endif