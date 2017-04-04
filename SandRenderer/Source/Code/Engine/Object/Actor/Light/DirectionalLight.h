#ifndef DirectionalLight_h
#define DirectionalLight_h

#include <Engine/Object/Actor/Light/Light.h>

namespace Sand
{
	/*
		�����ṹ
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
			�����ṹָ�룬�Ա����Ǵ�ȡ��������
		*/
		DirectionalLightStructure* m_pDirectionLightStructure;

		/*
			DirectionalLight�����Ԫ����Ŀ
		*/
		int m_iElementCount;

		/*
			���ڿ���StrcutureParameter����������д��
		*/
		StructureParameterWriter* m_pDirectionalLightStructureWriter;
	};
};
#endif