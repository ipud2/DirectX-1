#ifndef VVERTEX_H
#define VVERTEX_H

namespace Sand
{
#define MAX_SKIN_BONE_NUM	4

	class VVertex
	{
	public:
		VVertex( EInputMask eInputMask );

		void SetPosition( float x , float y , float z );

		void SetNormal( float x , float y , float z );

		void SetTangent( float x , float y , float z );

		void SetTexcoord( int iSet , float u , float v );

		void SetColor( float r , float g , float b );

		void AddWeight( int iJointIndex , float fJointWeight );
		
		bool GetPosition( float& x , float& y , float& z );

		bool GetNormal( float& x , float& y , float& z );

		bool GetTangent( float& x , float& y , float& z );

		bool GetTexcoord( float& x , float& y );

		void GetColor( float& r , float& g , float& b );

		bool GetWeight( int iWeightIndex , int32& iJointIndex , float& iJointWeight );

		int  GetWeightCount();

	protected:
		float		m_aPos[3];
		float		m_aNormal[3];
		float		m_aTangent[3];
		float		m_aTexcoord[2];
		float		m_aColor[3];
		EInputMask	m_eInputMask;
		int32		m_iJointNum;
		uint32		m_aJointIndex[MAX_SKIN_BONE_NUM];
		float		m_aJointWeight[MAX_SKIN_BONE_NUM];
	};
}
#endif