#ifndef DirectionalLight_h
#define DirectionalLight_h

#include <Engine/Object/Actor/Light/Light.h>

namespace Sand
{
	/*
		方向光结构
	*/
	struct DirectionalLightStructure
	{
		Vector4f AmbientLight;
		Vector4f DiffuseLight;
		Vector4f SpecularLight;

		Vector4f LightDirection;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight( int ElementCount );
		virtual ~DirectionalLight();

		void SetDirectionalLight( const Vector4f & AmbientLight , const Vector4f& DiffuseLight , const Vector4f& SpecularLight , const Vector4f& LightDirection , int index );

	protected:
		/*
			方向光结构指针，以便我们存取多个方向光
		*/
		DirectionalLightStructure* m_pDirectionLightStructure;

		/*
			DirectionalLight数组的元素数目
		*/
		int m_iElementCount;

		/*
			用于控制StrcutureParameter类对象的数据写入
		*/
		StructureParameterWriter* m_pDirectionalLightStructureWriter;
	};
};
#endif